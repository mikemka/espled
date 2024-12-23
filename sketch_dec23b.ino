#include <SPI.h>
#include <WiFi.h>
#include <WebServer.h>
#include "led_functions.h"
#include "network_functions.h"
#include "settings.h"


WebServer server(80);


void setup () {
  Serial.begin(115200);

  setupLEDPins();

  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.setHostname(WIFI_HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    processColor(500, 3, 255, 0, 0, true);
  }

  server.on("/", handle_OnConnect);
  server.on("/setcolor", handle_SetColor);
  server.begin();

  Serial.print("\nWiFi connected.\nIP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());

  processColor(500, 4, 0, 255, 0, true);

  write5v(255, 100, 255);
}


void loop () {
  server.handleClient();
}


void handle_OnConnect () {
  server.send(200, "text/html", SendHTML()); 
}

void handle_SetColor() {
  int r_5 = constrain(server.arg("r_5").toInt(), 0, 255);
  int g_5 = constrain(server.arg("g_5").toInt(), 0, 255);
  int b_5 = constrain(server.arg("b_5").toInt(), 0, 255);

  int r_12 = constrain(server.arg("r_12").toInt(), 0, 255);
  int g_12 = constrain(server.arg("g_12").toInt(), 0, 255);
  int b_12 = constrain(server.arg("b_12").toInt(), 0, 255);

  write5v(r_5, g_5, b_5);
  write12v(r_12, g_12, b_12);
  
  String response = "5v RGB(" + String(r_5) + "," + String(g_5) + "," + String(b_5) + ")\n12v RGB(" + String(r_12) + "," + String(g_12) + "," + String(b_12) + ")";
  server.send(200, "text/plain", response);
}

