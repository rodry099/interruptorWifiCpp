#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void muestraPagina() {
  String pagina;
   File f = SPIFFS.open("/index.html", "r");
  if(!f){
    Serial.print("error al abrir archivo");
  }
  server.send(200, "text/html", f.readString());
  f.close();
}
