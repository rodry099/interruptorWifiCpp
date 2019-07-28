#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void arranqueNormalJson(){

 //***********************************************************
//carga archivo configuracion y lo convierte en un objeto Json
//************************************************************

File setup = SPIFFS.open("/configuracion.txt", "r");
   if(!setup){
     Serial.println("No existe el archivo");
     setup.close();
     return;
   }
     StaticJsonBuffer<512> jsonBuffer;
     JsonObject &root = jsonBuffer.parseObject(setup);
     const char* ssid = root["ssid"];
     const char* password = root["password"];
     //const char* id = root["id"];
     int canales = root["canales"];
     //const char* servidorMqtt = root["servidor"];
     int reg = root["registrado"];
     setup.close();
     id_disp = String((const char*)root["id"]);
     NumCanales = canales;
     ServerMqtt = String((const char*)root["servidor"]);
     categoria = String((const char*)root["categoria"]);
     servidorNodeRed = String((const char*)root["servidorNodeRed"]); Serial.println(servidorNodeRed);
     registrado = reg; //guarda en variable global registrado el valor de reg 0= no registrado 1= registrado
                      // valor inicial igual a no registrado en el sistema

  //**********************************************
 //           conectando a red WiFi
 //***********************************************

 //conecta a router

 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

            Serial.println("");
            Serial.println("WiFi conectada");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            //***********************************************************
           //carga archivo configuracion y lo convierte en un objeto Json
           //************************************************************

                root.remove("ssid");
                root.remove("password");
                root.remove("servidor");

                if(registrado == 0){
                  root["canales"] = 1;
                }else{
                  root["canales"] = registrado + 1;
                }
                output = "";
                root.printTo(output);
                Serial.println("datos" + output);

}
