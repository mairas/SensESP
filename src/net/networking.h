#ifndef _networking_H_
#define _networking_H_

#include "Arduino.h"

// Local WebServer used to serve the configuration portal
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

#include "system/configurable.h"
#include "system/observable.h"

class Networking : public Configurable {
 public:
  Networking(String id, String schema="");
  void setup(std::function<void(bool)> connection_cb);
  ObservableValue<String>* get_hostname();
  virtual JsonObject& get_configuration(JsonBuffer& buf) override final;
  virtual void set_configuration(const JsonObject& config) override final;
  
  void set_hostname(String hostname);

  void reset_settings();

 protected:
  void check_connection();
 private:
  AsyncWebServer* server;
  DNSServer* dns;
  AsyncWiFiManager* wifi_manager;
  ObservableValue<String> hostname(String());
};

#endif