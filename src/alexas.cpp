#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void controlOne(EspalexaDevice* d){

  String encendido;

  if (d == nullptr) return; //this is good practice, but not required

  if (d->getValue()){
    encendido = "ON";
  }
  else {
    encendido = "OFF";
  }
 interruptor(1,encendido);
}

#ifdef ESP12E
void controlTwo(EspalexaDevice* d){

  String encendido;

  if (d == nullptr) return; //this is good practice, but not required

  if (d->getValue()){
    encendido = "ON";
  }
  else {
    encendido = "OFF";
  }

 interruptor(2,encendido);
}
#endif
