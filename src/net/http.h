#ifndef _http_H_
#define _http_H_

#include <ESPAsyncWebServer.h>

class HTTPServer {
 public:
  HTTPServer();
  ~HTTPServer() { delete server; }
  void enable() { server-> begin(); }
  void handle_not_found(AsyncWebServerRequest* request);
  void handle_config(AsyncWebServerRequest* request);
  void handle_device_reset(AsyncWebServerRequest* request);
  void handle_device_restart(AsyncWebServerRequest* request);
  void handle_info(AsyncWebServerRequest* request);
  void handle_system_hostname(AsyncWebServerRequest* request);
  void handle_system_signalk_address(AsyncWebServerRequest* request);
 private:
  AsyncWebServer* server;
};


#endif
