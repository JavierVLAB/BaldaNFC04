#pragma once

#include <iostream>
#include "ofMain.h"

#ifndef ARDUINOS_H_INCLUDED
#define ARDUINOS_H_INCLUDED

class Arduinos {

public:
    Arduinos();
    void lee();

    int nArduinos;

    ofSerial    *serial;
    string      *tarjeta;

};

#endif // ARDUINOS_H_INCLUDED
