#include <Arduino.h>

#ifndef GLOBALES_H
#define GLOBALES_H

//Variables **********************

extern long lastreconnectattempt;
extern long anunciaDisposito;

/****************************************************************************
Solo para modulos capacitivos con ttp223
canal 1 Gpio 13 salida Gpio 14
canal 2 Gpio 12 salida Gpio 16
*****************************************************************************/
extern int InterruptorOne;
extern int InterruptorTwo;
/****************************************************************************
Gpio relay 16 para interruptor esp8285 y 14 y 16 esp12e doble relay mecanico
*****************************************************************************/
extern int relayOne;
extern int relayTwo;
extern String id_disp;
extern int NumCanales;
extern String output;
extern String canal;
extern String willmsg; //topic direccion dispositivo
extern String ServerMqtt; // direccion del Brokker mqtt
extern String categoria; //categoria del dispositivo
extern String servidorNodeRed;
extern int registrado;
extern int canalDispositivo;
extern const char* estadoDispositivo;

#endif