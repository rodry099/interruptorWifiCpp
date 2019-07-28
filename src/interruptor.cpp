#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void interruptor(int canal, String estado){

  int gpioNum;
  if(canal == 1) gpioNum = relayOne;
  if(canal == 2) gpioNum = relayTwo;

  estado.toLowerCase();
  int encender;
  int onoff;

  if(estado.equals("on")){
    encender = 1;
  }else{
    encender = 0;
  }

  if(canal == 1){

    onoff = digitalRead(gpioNum);

    if(onoff == encender){
       return;
     }else{
         digitalWrite(gpioNum, encender);
     }
    Serial.println(estado);
  }
}
