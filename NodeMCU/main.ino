#include <WiFiServerSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <ESP8266WiFiGeneric.h>
#include <WiFiUdp.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiServerSecureAxTLS.h>
#include <BearSSLHelpers.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WiFiAP.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiType.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266HTTPClient.h>

#include <cruzamento.h>

const char* SSID = "";
const char* PASS = "";

HTTPClient http;

const String LOCATION = "http://semaforo-inteligente.herokuapp.com/";

const String UPLOAD = "upload";
const String DOWNLOAD = "download";

const String QTD_VIA1 ="\"QTD_VIA1\":";
const String QTD_VIA2 ="\"QTD_VIA2\":";
const String ORDEM_AMARELO ="\"ORDEM_AMARELO\":";
const String ORDEM_VERMELHO ="\"ORDEM_VERMELHO\":";

Cruzamento cruzamento(16, 5, 4, 14, 12, 13, 15, 0, 2);

void setup() {
  Serial.begin(115200);

  WiFi.begin(SSID, PASS);    //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.println(" Aguardando conexão");
  }

  cruzamento.LigarSemaforo();
}

void loop() {
   if(Serial.available() > 0){
      String comando = Serial.readString(); //Leitura da nova informação (JSON) pela porta serial atrelada ao Qt
      atualizarFuncoes(comando);
      Serial.print(JSON_ORDEM_VERMELHO());
      Serial.print(JSON_ORDEM_AMARELO()); 
      uploadORDEM_VERMELHO();
      uploadORDEM_AMARELO();  
    }

    if(cruzamento.estadoAmarelo()==1){
      cruzamento.amareloPiscando();
    }

    cruzamento.verifChegada();
    cruzamento.verifSensors();
    
    uploadQTDVIA_1();
    uploadQTDVIA_2();
    uploadORDEM_VERMELHO();
    uploadORDEM_AMARELO();

    atualizarFuncoes(downloadWEB());

    Serial.print(JSON_QTDVIA1());
    delay(10);
    Serial.print(JSON_QTDVIA2());
    delay(10);
    Serial.print(JSON_ORDEM_VERMELHO());
    delay(10);
    Serial.print(JSON_ORDEM_AMARELO());
    delay(10);
}

void uploadQTDVIA_1(){
    http.begin(LOCATION+UPLOAD); 
    http.addHeader("Content-Type", "application/json"); 
    http.POST(JSON_QTDVIA1()); 
    http.end();  
}

void uploadQTDVIA_2(){
    http.begin(LOCATION+UPLOAD); 
    http.addHeader("Content-Type", "application/json"); 
    http.POST(JSON_QTDVIA2()); 
    http.end();  
}

void uploadORDEM_VERMELHO(){
      
      http.begin(LOCATION+UPLOAD); 
      http.addHeader("Content-Type", "application/json"); 
      http.POST(JSON_ORDEM_VERMELHO()); 
      http.end();  
}

void uploadORDEM_AMARELO(){
      
      http.begin(LOCATION+UPLOAD); 
      http.addHeader("Content-Type", "application/json"); 
      http.POST(JSON_ORDEM_AMARELO()); 
      http.end();  
}

String downloadWEB(){
  
      http.begin(LOCATION+DOWNLOAD); 
      http.GET();
      String payload = http.getString();
      http.end();
      return payload;  
}

String JSON_QTDVIA1(){

    return "{" +
               QTD_VIA1 + String(cruzamento.getQtdViaPrimaria()) + 
           "}";
}

String JSON_QTDVIA2(){

    return "{" +
               QTD_VIA2 + String(cruzamento.getQtdViaSecundaria()) + 
           "}";
}

String JSON_ORDEM_VERMELHO(){

    return "{" + 
                  ORDEM_VERMELHO + String(cruzamento.estadoPedestres()) +
            "}";
}

String JSON_ORDEM_AMARELO(){

    return "{" + 
                  ORDEM_AMARELO + String(cruzamento.estadoAmarelo()) +
            "}";
}

void atualizarFuncoes(String comando){

  if(comando.startsWith("{") && comando.endsWith("}")){ 

    if(cruzamento.estadoAmarelo()==0){
      if(comando.indexOf(ORDEM_VERMELHO +" 1") > 0){
        cruzamento.abrirPedestres();
      }else if(comando.indexOf(ORDEM_VERMELHO +" 0") > 0){
        cruzamento.fecharPedestres();
      } 
    }

    if(cruzamento.estadoPedestres()==0){
      if(comando.indexOf(ORDEM_AMARELO +" 1") > 0){
        cruzamento.amareloPiscando();
      }else if(comando.indexOf(ORDEM_AMARELO +" 0") > 0){
        cruzamento.amareloParar();
      }
    }
  }
}
