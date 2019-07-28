#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "Arduino.h"

void configInicial();
void muestraPagina();
void arranqueNormal();
void arranqueNormalJson();
void guarda_config();
boolean reconnect();
void registerDevice(String);
void numeraDispositivo(String);
void interruptor(int, String);

//Rutinas Callbacks
void callback(char*, byte*, unsigned int);
void controlOne(EspalexaDevice* dev);
void controlTwo(EspalexaDevice* dev);

#endif