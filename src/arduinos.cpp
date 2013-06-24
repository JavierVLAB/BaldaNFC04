#include "arduinos.h"
#include "funciones.h"
#include "ofMain.h"

#ifndef ARDUINOS_H_INCLUDED
#define ARDUINOS_H_INCLUDED

Arduinos::Arduinos{

    nArduinos = 1;

    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;

    serial = new ofSerial[nArduinos];
    trajeta = new string[nArduinos];

    for(int i = 0; i < nArduinos; i++){
        serial[i].setup(i, baud);
    }

}

void Arduinos::lee(){


    for(int i = 0; i < nArduinos; i++){
        string lectura;
        unsigned char bytesLeidos[120];
        memset(bytesLeidos,0,120);
        int numbyteLeidos = serial.readBytes(bytesLeidos,120);

        if(numbytesLeidos > 0){
            lectura = ofToString(bytesLeidos);

            vector< string > partes = ofSplitString(lectura, "\n");

            for(int j = 0; j < partes.size(); j++){
                if(partes[j].size() == 35){
                    tarjeta[i] = partes[j];
                }

            }

        } else {tarjeta[i] = "";}

        ofLog(OF_LOG_NOTICE, tarjeta[i]);

    }

}


#endif // ARDUINOS_H_INCLUDED
