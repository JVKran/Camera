#include <WiFi.h>
#include <PubSubClient.h>
#include "Camera.hpp"
#include "TimeLapse.hpp"

Camera camera;
// TimeLapse timeLapse;

const char* ssid = "KraanBast2.4";
const char* password = "Snip238!";
const char* mqttServer = "192.168.178.81";
uint32_t lastMessage = 0;
bool motion = false;
uint8_t pirPin = 13;

WiFiClient espClient;
PubSubClient client(espClient);

void setupWifi(){
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(50);
    }
}

void reconnect() {
  while (!client.connected()) {
    if (!client.connect("Camera", "Camera", "Snip238!")) {
      delay(500);
    }
  }
}

void setup() {
    pinMode(pirPin, INPUT);
    camera.begin();
    //timeLapse.begin();
    setupWifi();
    client.setServer(mqttServer, 1883);
    camera.startServer();
}

void loop() {
    //timeLapse();
    if (!client.connected()) {
        reconnect();
        client.publish("test", "Connected!");
    }
    client.loop();
    if(millis() - lastMessage > 5000){
        client.publish("test", "Checkup call!");
        lastMessage = millis();
    }
    if(digitalRead(pirPin) == HIGH){
        client.publish("test", "Movement Detected!");
        delay(1000);
    }
}
