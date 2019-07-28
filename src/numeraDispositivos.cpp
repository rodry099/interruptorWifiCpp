#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void numeraDispositivo(String salida){
  StaticJsonBuffer<512> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(salida);
  if(registrado == 0) return;
  String nombreMas = id_disp;
  nombreMas += " ";
  nombreMas += registrado + 1;
  root["id"] = nombreMas;
  output = "";
  root.printTo(output);
}
