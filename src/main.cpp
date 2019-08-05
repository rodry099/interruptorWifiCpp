#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

/* elija aqui para que dispositivo y configuracion quiere compilar 
    por defecto compila para un esp8285 con un solo canal          */

//#define ESP12E     /*descomentar si se compila para esp12e con dos relay*/
//#define ESP12EONE  /*descomentar si se compila para esp12e con un relay*/
//#define ONETTP223 /*con un sensor capacitivo*/
//#define TWOTTP223 /*con dos sensores capacitivos*/

WiFiClient espClient;
PubSubClient client(espClient);
Espalexa espalexa;

long lastreconnectattempt = 0;
long anunciaDisposito = 0;
/****************************************************************************
Solo para modulos capacitivos con ttp223
canal 1 Gpio 13 salida Gpio 14
canal 2 Gpio 12 salida Gpio 16
*****************************************************************************/
int InterruptorOne = 13;
int InterruptorTwo = 12;
/****************************************************************************
Gpio relay 16 para interruptor esp8285 y 14 y 16 esp12e doble relay mecanico
*****************************************************************************/
int relayOne = 16;
int relayTwo = 14;

String id_disp = "";
int NumCanales;
String output = "";
String canal;
String willmsg; //topic direccion dispositivo
String ServerMqtt; // direccion del Brokker mqtt
String categoria; //categoria del dispositivo
String servidorNodeRed;
int registrado = 0;
int canalDispositivo;
const char* estadoDispositivo;

//Inicializacion Wifi **************
IPAddress ip(192, 168, 0, 1);
ESP8266WebServer server(80);
//WiFiServer servidor(8080);

void setup() {
   Serial.begin(115200);
   bool result = SPIFFS.begin();
   Serial.println("SPIFFS opened: " + result);

     File f = SPIFFS.open("/configuracion.txt", "r");
      if(!f){
        f.close();
        configInicial(); //inicia como AP y permite configurar conexion a router
      }

    // inicia normalmente conectando a la red que se haya configurado

    arranqueNormalJson();
    client.setServer(ServerMqtt.c_str(), 1883);
    client.setCallback(callback);
    #ifdef ESP12E
    String deviceOne = id_disp + " uno";
    String deviceTwo = id_disp + " dos";
    espalexa.addDevice(deviceOne, controlOne, EspalexaDeviceType::onoff);
    espalexa.addDevice(deviceTwo, controlTwo, EspalexaDeviceType::onoff);
    #else
    espalexa.addDevice(id_disp, controlOne, EspalexaDeviceType::onoff);
    #endif
    espalexa.begin();
    ArduinoOTA.begin();

    #ifdef ESP12E
    pinMode(InterruptorOne,INPUT);
    pinMode(InterruptorTwo,INPUT);
    digitalWrite(InterruptorOne, 0);
    digitalWrite(InterruptorTwo, 0);
    pinMode(relayOne, OUTPUT);
    pinMode(relayTwo, OUTPUT);

    #else
    pinMode(InterruptorOne,INPUT);
    digitalWrite(InterruptorOne, 0);
    pinMode(relayOne, OUTPUT);

    #endif

    lastreconnectattempt = 0;
    //NumCanales = registrado;
    if(registrado > 0){
      Serial.println("Dispositivo registrado en el sistema");
    }
}

void loop() {

    ArduinoOTA.handle();

    client.loop();
    delay(1);


    espalexa.loop();
    delay(1);

#ifdef ONETTP223

  if(digitalRead(InterruptorOne)){
     interruptor(1);
     delay(1000);
 }

 #endif

 #ifdef TWOTTP223

  if(digitalRead(InterruptorTwo)){
     interruptor(2);
     delay(1000);
 }

  #endif

 if (!client.connected()) {
    long now = millis();
    if(now - lastreconnectattempt >5000){
      lastreconnectattempt = now;
      if(reconnect()){
        lastreconnectattempt = 0;
      }
    }
  }

  if(registrado < NumCanales){
    long ahora = millis();
      if(ahora - anunciaDisposito > 5000){
        anunciaDisposito = ahora;
      client.publish("devices", output.c_str());
      Serial.println("Not registered");
      numeraDispositivo(output);
      Serial.println(output);
    }
  }
  
}
