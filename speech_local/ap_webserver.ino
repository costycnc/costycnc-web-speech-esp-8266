#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char *ssid = "ESP8266 Access Point"; // The name of the Wi-Fi network that will be created
const char *password = "thereisnospoon";   // The password required to connect to it, leave blank for an open network

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
pinMode(LED_BUILTIN, OUTPUT);
  //WiFi.softAP(ssid, password);             // Start the access point
  WiFi.softAP(ssid);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
    server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
    server.on("/on", HTTP_GET, on);     // Call the 'handleRoot' function when a client requests URI "/"
    server.on("/off", HTTP_GET, off);     // Call the 'handleRoot' function when a client requests URI "/"
    server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop() { 
  server.handleClient();
  }
/*
  void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}

*/

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "Hello costycnc");
}
void on() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "Hello costycnc on");
  digitalWrite(LED_BUILTIN, LOW);
}
void off() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "Hello costycnc off");
  digitalWrite(LED_BUILTIN, HIGH);
}
