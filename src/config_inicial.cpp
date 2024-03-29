#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void configInicial(){
  uint32_t chipId = ESP.getFlashChipId();
  String ssidID = "";
  ssidID = chipId;
  String ssid = "DOMO";
  ssid += ssidID.substring(3);
  Serial.println(chipId);
  const char *password = "1234567890";
  IPAddress ip(192, 168, 0, 1);
  server.begin();
  Serial.println();
      Serial.print("Configuring access point...");
      WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0));
      WiFi.softAP(ssid.c_str(), password);
        server.on("/", muestraPagina);
        server.on("/CONFIGURACION",HTTP_GET, guarda_config);
        server.begin();
      Serial.println("HTTP server started");

          while(true){
            server.handleClient();
          }
    }
