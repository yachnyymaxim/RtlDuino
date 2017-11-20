
/*
 This sketch shows how use webserver serving from SD card
 and i show u howto receive payload binary data in POST.
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


SdFatFs fs;
Config_t cfg = {"wifi","password","1",false};

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
void handleCmd(){

  //get plain data "plain" is special arg name for payload data
  //  (data was send not as form but as binary payload)
  //sending binary data is better than parsing text arguments
  //but for simple data (string, int ... u may use form arguments)
  String str = server.arg("plain");
  for(int i = 0; i < str.size(); ++i){
    printf(" %d ",str.data()[i]);
  }
 printf("\n");
server.send(200,"application/octet-stream",str);
}


void handleNotFound(){
  printf("file %s \n",server.uri().c_str());
  //this method serving files from document root "/www" in this case
  int st = server.serveStatic(fs,"/www/");
  printf("status %d \n", st);
  if(st != -1 )
        return;
  server.send(404, "text/plain", "File Not Found\n\n");
}


void setup() {
    InitCryptoEngine();
    fs.begin();
    setupWIFI();
    
    
    server.on("/cmd",handleCmd);
    server.on("/inline", [](){
        server.send(200, "text/plain", "this works as well");
     });

    server.onNotFound(handleNotFound);

    server.begin();

}

void loop() {
  
    server.handleClient();

}
