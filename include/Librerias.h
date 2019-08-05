#ifndef LIBRERIAS_H
#define LIBRERIAS_H
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266WebServer.h>
    #include <ESP8266mDNS.h>
    #include <WiFiUdp.h>
    #include <ArduinoOTA.h>
    #include <FS.h>
    #include <Wire.h>
    #include <PubSubClient.h>
    #include <ArduinoJson.h>
    #include <Espalexa.h>
    //declaracion de objetos sin inicializar
    //inicializar solo una vez en cualquier lugar
    extern WiFiClient espClient;
    extern PubSubClient client;
    extern Espalexa espalexa;
    extern IPAddress ip;
    extern ESP8266WebServer server;
#endif