#include <Arduino.h>
#include "Librerias.h"
#include "Globales.h"
#include "Funciones.h"

void callback(char* topic, byte* payload, unsigned int length){

  int channel;
  String estadoDevuelto = "";
  String solicitud = servidorNodeRed + "/" + categoria + "/" + id_disp + "/feedback";
  String respuestaEstado = servidorNodeRed + "/estadoDispositivos";

  const int capacity = JSON_OBJECT_SIZE(4);
  StaticJsonBuffer<capacity> DatosMqtt;
  char datos[80];
  unsigned int i=0;
  for (i=0;i<length;i++) {
    datos[i] = (char)payload[i];
  }
  JsonObject& obj = DatosMqtt.parseObject(datos);

      if (obj.success()) {
          //Serial.println("parseObject() succeeded");
        } else {
        //Serial.println("parseObject() FAILED");
        }
        canalDispositivo = obj["canal"];
        estadoDispositivo = obj["status"];

        String onOff(estadoDispositivo);
        String Stopic(topic);

        Serial.println(canalDispositivo);
    /***************************************
      Enciende y apaga luz
    ***************************************/
      if(canalDispositivo > 0){
        if(canalDispositivo == 1) channel = relayOne;
        else channel = relayTwo;
        estadoDispositivo = (digitalRead(channel) == 0)? "on":"off";
        interruptor(canalDispositivo,estadoDispositivo);
        Serial.println(estadoDispositivo);
      }
    /***************************************
      si recibe el topic device/setup
      llama a la subrutina registerDevices
      y guarda 1 en la variable registrado
      del archivo configuracion
    ***************************************/
    if(Stopic.equals("device/setup")){
      registerDevice(estadoDispositivo);
      registrado = 1;
      anunciaDisposito = 0;
      ESP.restart();
      return;
    }

    /*****************************************
     * devuelve estado del dispositivo
     *****************************************/
    if(Stopic.equals(solicitud)){
      Serial.println("solicitan estado");
      int result = digitalRead(relayOne);
      if(result == 1){
        estadoDevuelto = "on";
      }else{
        estadoDevuelto = "off";
      }
      client.publish(respuestaEstado.c_str(), estadoDevuelto.c_str());
    }
}
