#ifndef SENSESP_APP_BUILDER_H
#define SENSESP_APP_BUILDER_H

#include "sensesp_app.h"

class SensESPBareAppBuilder {
 private:
  String hostname_ = "SensESP";
  String ssid_ = "";
  String password_ = "";
  String sk_server_address_ = "";
  uint16_t sk_server_port_ = 0;

 protected:
  SensESPApp* app_;

  bool networking_enabled_ = false;
  bool http_server_enabled_ = false;
  bool websocket_client_enabled_ = false;

 public:
  SensESPBareAppBuilder() { app_ = new SensESPApp(true); }

  SensESPBareAppBuilder* enable_networking() {
    networking_enabled_ = true;
    app_->set_enable_networking();
    return this;
  }
  SensESPBareAppBuilder* enable_http_server() {
    http_server_enabled_ = true;
    app_->set_enable_http_server();
    return this;
  }
  SensESPBareAppBuilder* enable_websocket_client() {
    websocket_client_enabled_ = true;
    app_->set_enable_websocket_client();
    return this;
  }

  virtual SensESPBareAppBuilder* set_ota(String password) {
    enable_networking();
    // TODO: implement
    //app_->set_ota(password);
    return this;
  }

  virtual SensESPBareAppBuilder* set_wifi(String ssid, String password) {
    enable_networking();
    app_->set_ssid(ssid);
    app_->set_wifi_password(password);
    return this;
  }
  virtual SensESPBareAppBuilder* set_sk_server(String address, uint16_t port) {
    enable_websocket_client();
    app_->set_sk_server_address(address);
    app_->set_sk_server_port(port);
    return this;
  }
  virtual SensESPBareAppBuilder* set_hostname(String hostname) {
    app_->set_preset_hostname(hostname);
    return this;
  }
  virtual SensESPBareAppBuilder* set_system_status_led(SystemStatusLed* system_status_led) {
    app_->set_system_status_led(system_status_led);
    return this;
  }
  virtual SensESPBareAppBuilder* set_test_auth_on_each_connect(bool val) {
    WSClient::test_auth_on_each_connect_ = val;
    return this;
  }
  virtual SensESPApp* get_app() {
    app_->setup();
    return app_;
  }
};

/**
 * @brief A class for quickly configuring a SensESP application object before
 * wiring up your sensors.
 */
class SensESPAppBuilder : public SensESPBareAppBuilder {
 private:
  
 public:
  SensESPAppBuilder() { 
    enable_networking();
    enable_http_server();
    enable_websocket_client();
  }
};

#endif