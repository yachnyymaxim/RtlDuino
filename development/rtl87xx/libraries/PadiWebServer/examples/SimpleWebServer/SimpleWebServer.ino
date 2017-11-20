
/*
 This sketch shows how use simple padiwebserver.
 */
#include "SdFatFs.h"

#include <WiFi.h>
#include "rtl_crypto.h"
#include <PadiWebServer.h>

#define printf rtl_printf

struct Config_t {
      char  ssid[20];
      char  passwd[22];
      char channel[3];
      bool ap;     
};

Config_t cfg = {"yourwifi","yourwifipass","1",false};

int status = WL_IDLE_STATUS;     // the Wifi radio's status
PadiWebServer server(80);

void setupWIFI(){
  
  WiFi.status(); //this magic init wifi
  if (cfg.ap){
   //if(1){
   // attempt to start AP:
      while (status != WL_CONNECTED) {
         printf("Attempting to start AP with SSID:%s\n ", cfg.ssid);
         status = WiFi.apbegin(cfg.ssid, cfg.passwd, cfg.channel);
         delay(10000);
       }

  }else{
      // attempt to connect to Wifi network:
      while (status != WL_CONNECTED) {
        printf("Attempting to connect to WPA SSID: %s\n",cfg.ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(cfg.ssid, cfg.passwd);
        // wait 10 seconds for connection:
        delay(20000);
      }  
      IPAddress ip = WiFi.localIP();
      printf("IP is %s\n ", ip.get_address());
  }
}

void handleRoot() {
  server.send(200, "text/plain", "hello from Padi!");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
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
}


void setup() {
    InitCryptoEngine();
    setupWIFI();
    server.on("/", handleRoot);

    server.on("/inline", [](){
        server.send(200, "text/plain", "this works as well");
     });

    server.onNotFound(handleNotFound);

    server.begin();

}

void loop() {
  
    server.handleClient();

}
