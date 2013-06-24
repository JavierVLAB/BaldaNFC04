#include <iostream>
#include <string>
#include "zapatilla.h"
#include "funciones.h"
#include "ofMain.h"

#ifndef ZAPATILLA_CPP_INCLUDED
#define ZAPATILLA_CPP_INCLUDED

Producto::Producto(){
    // inicializamos el objeto producto
    for(int i = 0; i < 3; i++){
        tarjeta[i] = "";
        alive[i] = false;
    }
}

Zapatilla::Zapatilla(){

    // Descarga del XML
    // se hace diferente si se esta en WIN o en RPI
    // el archivo se mueve y se sobreescribe, esto esta bien porque si no lo
    // descarga usa el bajado anteriormente

    if(OS == "WIN"){

        system ("wget http://www.barrabes.com/downloads/zapatillas_trail_running.xml");
        system ("xcopy zapatillas_trail_running.xml data /y");
        system ("del zapatillas_trail_running.xml");

    }

    if(OS == "RPI"){

        system ("wget http://www.barrabes.com/downloads/zapatillas_trail_running.xml");
    	system ("mv -f zapatillas_trail_running.xml bin/data/");

    }

    //Cargamos el XML y definimos todas las variables

    ofxXmlSettings XML;

    XML.loadFile("zapatillas_trail_running.xml");
    XML.pushTag("rss");
    XML.pushTag("channel");

	num = XML.getNumTags("item");

    img = new ofImage[num];
    hombre = new bool[num];
    marca = new string[num];
    modelo = new string[num];
    color = new string[num];
    descrip = new string[num];
    tallas = new string[num];
    id = new int[num];
    precio = new float[num];
    oferta = new float[num];
    caract.resize(num);
    tarjeta = new string[num];

    for(int i = 0; i < num; i++){
        XML.pushTag("item",i);
        marca[i] = LimpiaTexto(XML.getValue("marca",""));
        modelo[i] = LimpiaTexto(XML.getValue("nombre",""));
        string genero = XML.getValue("sexo","");
        if(genero == "Hombre"){
            hombre[i] = true;
        } else {
            hombre[i] = false;
        }
        color[i] = LimpiaTexto(XML.getValue("color",""));
        id[i] = XML.getValue("identificacion",0);
        precio[i] = XML.getValue("precio",0.0);                //Valor 5 de la API
        oferta[i] = XML.getValue("precioOferta",0.0);
        descrip[i] = LimpiaTexto(XML.getValue("descripcion",""));

        caract[i].resize(8);
        XML.pushTag("caracteristicas");
        int numCaracteristicas = XML.getNumTags("caracteristica");
        for(int j = 0; j < numCaracteristicas; j++){
            XML.pushTag("caracteristica");
            caract[i][j].resize(2);
            caract[i][j][0] = LimpiaTexto(XML.getValue("nombre",""));
            caract[i][j][1] = LimpiaTexto(XML.getValue("valor",""));
            XML.popTag(); // Salir de caracteristica
        }
        XML.popTag(); // Salir de caracteristicas

        string imagenURL = XML.getValue("imagen","");
        vector<string> partes = ofSplitString(imagenURL, "/");
        string imagenFile = partes[partes.size()-1];

        if(OS == "WIN"){
            //Igual que antes movemos sobreescribimos y si no ha bajado usamos anterior
            imagenURL = "wget " + imagenURL;
            system(imagenURL.c_str()); // esto es necesario porque imagen es un string y no un char*
            imagenURL = "xcopy " +  imagenFile + " data /y";
            system (imagenURL.c_str());
            imagenURL = "del " + imagenFile;
            system (imagenURL.c_str());
        }

        if(OS == "RPI"){

            imagenURL = "wget " + imagenURL;
            system(imagenURL.c_str()); // esto es necesario porque imagen es un string y no un char*
            imagenURL = "mv -f " +  imagenFile + " data/";
            system (imagenURL.c_str());

        }


        img[i].loadImage(imagenFile);
        XML.popTag(); // Salir de item


    }

    //Cargamos .csv con la relacion tarjeta producto
    ofxCsv csv;
    csv.loadFile(ofToDataPath("Tarjetas.csv"),";");

    int nTarj = csv.data.size();
    string noTarj = "0x00 0x00 0x00 0x00 0x00 0x00 0x00";

    //Asociamos la tarjeta a cada producto
    for(int i = 0; i < nTarj; i++){
        for(int j = 0; j < num; j++){
            if(ofToInt(csv.data[i][0]) == id[j] && csv.data[i][1] != noTarj){
                tarjeta[j] = csv.data[i][1];
            }
        }
    }

    //Otras definiciones para dibujar
    ancho = (ofGetWidth()-200)/3;

    //Cargar fonts

    fontBold32.loadFont("SourceSansPro-Bold-webfont.ttf",32);
    fontSemibold18.loadFont("SourceSansPro-Semibold-webfont.ttf",18);
    fontExtralight38.loadFont("SourceSansPro-Extralight-webfont.ttf",38);
    fontExtralight36.loadFont("SourceSansPro-Extralight-webfont.ttf",36);
    fontExtralight18.loadFont("SourceSansPro-Extralight-webfont.ttf",18);

}

void Zapatilla::draw(Producto prod){

    int posicion = 0;
    while(posicion < 3){
        if(prod.alive[posicion]){//prod.alive[posicion]){
            int p = buscaTarjeta(prod.tarjeta[posicion]);

            ofSetColor(255,255,255);
            img[p].draw(100+(posicion+0.5)*ancho,150,400,400); //(100+(posicion+0.5)*ancho,350);

            /////Marca
            ofSetColor(68,68,68);
            fontExtralight36.drawString(marca[p],100+(posicion+0.8)*ancho, 555);

            //////Modelo
            fontBold32.drawString(modelo[p],100+(posicion+0.8)*ancho, 585);


            //////Precio
            fontBold32.drawString(ofToString(precio[p]),100+(posicion+0.8)*ancho, 635);

            /////Descripcion
            fontExtralight18.drawString("Descripción",90+(posicion+0.5)*ancho - 11*9, 680);

            fontSemibold18.drawString(descrip[p],100+(posicion+0.5)*ancho, 680);
        }
        posicion++;
    }

}

int Zapatilla::buscaTarjeta(string texto){

    for(int i = 0; i < num; i++){
        if(texto == tarjeta[i]){
            return i;
        }
    }

    return 0;
}

Arduino::Arduino(){

    nArduinos = 2;

    int baud = 9600;

    serial = new ofSerial[nArduinos];
    tarjeta = new string[nArduinos];

    vector <ofSerialDeviceInfo> deviceList = serial[0].getDeviceList();

    for(int i = 0; i < nArduinos; i++){
        serial[i].setup(i, baud);
    }

}

void Arduino::lee(Producto *prod){

    for(int i = 0; i < nArduinos; i++){
        string lectura;
        unsigned char bytesLeidos[120];
        memset(bytesLeidos,0,120);
        int numbytesLeidos = serial[i].readBytes(bytesLeidos,120);

        if(numbytesLeidos > 0){
            lectura = ofToString(bytesLeidos);
            vector< string > partes = ofSplitString(lectura, "\n");

            for(int j = 0; j < partes.size(); j++){

                if(partes[j].size() == 35){
                    tarjeta[i] = partes[j];
                    tarjeta[i].erase(34,1);
                }

            }

        } else {tarjeta[i] = "";}

        if(tarjeta[i] == ""){
            if(prod->alive[i]){
              prod->alive[i] = false;
              prod->tarjeta[i] = "";
            }

        } else {
            prod->tarjeta[i] = tarjeta[i];
            prod->alive[i] = true;

        }
    }
}


#endif // ZAPATILLA_CPP_INCLUDED
