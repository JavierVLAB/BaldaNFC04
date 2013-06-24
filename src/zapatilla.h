#pragma once

#include <iostream>
#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxXmlSettings.h"

#define OS "Prueba"

#ifndef ZAPATILLA_H_INCLUDED
#define ZAPATILLA_H_INCLUDED

using namespace wng; // esto es super importante sino no reconoce el ofxCsv type

class Producto {

public:
    Producto();

    string  tarjeta[3];
    bool    alive[3];

};


class Zapatilla {

public:
    Zapatilla();
    void draw(Producto prod);
    int buscaTarjeta(string texto);

    int num;
    ofImage *img;
    bool *hombre;
    string *marca;
    string *modelo;
    string *color;
    string *descrip;
    string *tallas;
    vector<vector<vector<string> > > caract; //string zapCaracteristicas[100][8][2];
    int *id;
    float *precio;
    float *oferta;
    string *tarjeta;

    int ancho;

    ofTrueTypeFont fontBold32;
    ofTrueTypeFont fontSemibold18;
    ofTrueTypeFont fontExtralight38;
    ofTrueTypeFont fontExtralight36;
    ofTrueTypeFont fontExtralight18;

};

class Arduino {

public:
    Arduino();
    void lee(Producto *prod);

    int nArduinos;

    ofSerial    *serial;
    string      *tarjeta;


};

#endif // ZAPATILLA_H_INCLUDED
