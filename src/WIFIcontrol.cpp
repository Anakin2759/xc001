#include <WiFi.h>
#include <WebServer.h>
#include <WIFIcontrol.h>
#include<freertos/freeRTOS.h>
#include<freertos/task.h>
#include<main.h>
#include"tracing.h"
#include"mada.h"
const char* ssid = "V1";
const char* password = "asdasdasd";


//IPAddress local_IP(192, 168, 137, 91);
//IPAddress gateway(192, 168, 1, 1);
//IPAddress subnet(255, 255, 255, 0);


WebServer server(80);
void wifiReady() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/turn_left1", turn_left1);
  server.on("/turn_right1", turn_right1);
  server.on("/stop1", stop1);
  server.on("/tracer", tracer);
  server.begin();
  Serial.println("HTTP server started");
  IPAddress localIP = WiFi.localIP();
  Serial.print("Local IP address: ");
  Serial.println(localIP.toString());
}

void wifirun() {
  while(1)
  server.handleClient();
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><title>ESP32WiFi遥控</title></head><body><h1>ESP32WiFi遥控</h1><table>";
  html += "<tr><td><a href=\"/on\"><button>前进</button></a></td><td><a href=\"/off\"><button>后退</button></a></td></tr>";
  html += "<tr><td><a href=\"/turn_left1\"><button>左转</button></a></td><td><a href=\"/turn_right1\"><button>右转</button></a></td></tr>";
  html += "<tr><td><a href=\"/stop1\"><button>停止</button></a></td><td><a href=\"/tracer\"><button>循迹启动\\关闭</button></a></td></tr>";
  html += "</table></body></html>";
  server.send(200, "text/html", html);
}//网页编辑

void handleOn() {
  uint32_t data = 0;
  xQueueSend(queue, &data, 1000);
  server.send(204);
}

void handleOff() {
  uint32_t data = 1;
  xQueueSend(queue, &data, 1000);
  server.send(204);
}
void turn_left1() {
  uint32_t data = 2;
  xQueueSend(queue, &data, 1000);
  server.send(204);
}
void turn_right1()
{
  uint32_t data = 3;
  xQueueSend(queue, &data, 1000);
  server.send(204);
}

void stop1()
{
  uint32_t data = 4;
  xQueueSend(queue, &data, 1000);
  server.send(204);
}

void tracer()
{
  uint32_t data = 5;
  xQueueSend(queue, &data, 1000);
  server.send(204);
}

void tracer_stop()
{
  uint32_t data = 6;
  xQueueSend(queue, &data, 1000);
  server.send(204);
}