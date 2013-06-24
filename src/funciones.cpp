#include <iostream>
#include "ofMain.h"
//#include "funciones.h"

#ifndef FUNCIONES_CPP_INCLUDED
#define FUNCIONES_CPP_INCLUDED

#define ANSIL 12

string ansiCode[] = {
  "&#225;", "&#241;", "&#243;", "&#237;", "&#250;", "&#233;", "&#246;", "&#39;", "&quot;", "&reg;", "<br>", "&#174;"
};
string ansiChar[] = {
  "á", "ñ", "ó", "í", "ú", "é", "ö", "'", "'", "®", "", "®"
};

string LimpiaTexto(string texto){
    string s = texto;
    for(int i = 0; i < ANSIL; i++){
       ofStringReplace(s,ansiCode[i],ansiChar[i]);
    }
    return s;
}


#endif // FUNCIONES_CPP_INCLUDED
