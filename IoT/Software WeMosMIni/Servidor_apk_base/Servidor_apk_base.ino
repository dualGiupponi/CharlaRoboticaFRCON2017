#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Automatismo";
const char* password = "19014760";

ESP8266WebServer server(80);

const int led = 2;  //Puerto TX Default
// en este caso, 0 lo apaga y 1 lo prende
const int ledR = 3; //D1
const int ledG = 4; //D2
const int ledB = 5; //D3



void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "ESP Iniciado");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 0);
  String message = "Archivo no encontrado!\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 1);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("Servidor MDNS iniciado");
  }

  server.on("/", handleRoot);

  server.on("/0", [](){
    server.send(200, "text/plain", "Apago LED");
     digitalWrite(led, 1);
  });
  
  server.on("/1", [](){
    server.send(200, "text/plain", "Enciendo LED ");
     digitalWrite(led, 0);
  });
  
  server.on("/21", [](){
    server.send(200, "text/plain", "Enciendo LED 2");
     digitalWrite(ledB, 0);
  });

  server.on("/20", [](){
    server.send(200, "text/plain", "Apago LED 2 ");
     digitalWrite(ledB, 0);
  });
    
  server.on("/31", [](){
    server.send(200, "text/plain", "Enciendo LED 3");
     digitalWrite(ledG, 0);
  });

  server.on("/30", [](){
    server.send(200, "text/plain", "Apago LED 3");
     digitalWrite(ledG, 0);
  });
    
  server.on("/41", [](){
    server.send(200, "text/plain", "Enciendo LED 4");
     digitalWrite(ledR, 0);
  });

  server.on("/40", [](){
    server.send(200, "text/plain", "Apago LED 4");
     digitalWrite(ledR, 0);
  });
  

  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor HTTP Iniciado ");
}

void loop(void){
  server.handleClient();
  if (Serial.available() > 0) {
   char value = Serial.read();
   if (value == 'd')
   {
  Serial.print("Conectado a ");
   Serial.println(ssid);
     Serial.print("Direccion IP: ");
       Serial.println(WiFi.localIP());
   }
   else if (value  == 'r')
   {
    Serial.println(analogRead(A0));
   }
   
}

  }
  

