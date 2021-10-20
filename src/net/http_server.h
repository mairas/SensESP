#ifndef _http_server_H_
#define _http_server_H_

#include <ESPAsyncWebServer.h>

#include <functional>

#include "system/enableable.h"

/**
 * @brief Handles external interactions with the device via the web interface.
 */
class HTTPServer : public Enableable {
 public:
  HTTPServer();
  ~HTTPServer() { delete server; }
  virtual void enable() override { server->begin(); }
  void handle_not_found(AsyncWebServerRequest* request);
  void handle_config(AsyncWebServerRequest* request);
  void handle_device_reset(AsyncWebServerRequest* request);
  void handle_device_restart(AsyncWebServerRequest* request);
  void handle_info(AsyncWebServerRequest* request);

 private:
  AsyncWebServer* server;
  void handle_config_list(AsyncWebServerRequest* request);
};

#endif
