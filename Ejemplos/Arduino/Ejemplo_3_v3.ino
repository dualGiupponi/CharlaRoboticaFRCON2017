#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "IoT";
const char* password = "alvlgeddl";

ESP8266WebServer server(80);

const int led = 2;  //Puerto TX Default
const int rele = D1 ; // Conector D1
const int analogOut = D3 ; // Conector D3




void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "ESP Iniciado, ¡TODO FUNCIONA!"); //Cuando pones la direccion ip unicamente te manda a este lugar
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
  pinMode(rele,OUTPUT);
  pinMode(analogOut,OUTPUT);
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

    server.on("/tv0", [](){
    server.send(200, "text/plain", "Enciendo LED ");
     digitalWrite(led, 0);
  });
  
  
  server.on("/valor", [](){
    
    String cadenaDeValor = server.arg("velocidad");
    float valorRecibidoTransformado = cadenaDeValor.toFloat();
    server.send(200, "text/plain", cadenaDeValor) ;
    Serial.println(valorRecibidoTransformado);
    analogWrite(analogOut,valorRecibidoTransformado);
    });
 
  server.on("/parada", [](){
  server.send(200, "text/plain", "Deteniendo Equipo...");
     digitalWrite(rele, 0);
  });
 
  server.on("/arranque", [](){
  server.send(200, "text/plain", "Arrancando Equipo...");
  digitalWrite(rele, 1);
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor HTTP Iniciado ");
}


// MONITOREO POR TERMINAL REMOTO
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
