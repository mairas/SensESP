#ifndef _http_H_
#define _http_H_

#include <ESPAsyncWebServer.h>

#include "app.h"

class HTTPServer {
 public:
  HTTPServer(SensESPApp* app);
  ~HTTPServer() { delete server; }
  void enable() { server-> begin(); }
  void handle_not_found(AsyncWebServerRequest* request);
  void handle_config(AsyncWebServerRequest* request);
  void handle_device_reset(AsyncWebServerRequest* request);
  void handle_device_restart(AsyncWebServerRequest* request);
  void handle_info(AsyncWebServerRequest* request);
 private:
  AsyncWebServer* server;
  SensESPApp* sensesp_app;
};


#endif
