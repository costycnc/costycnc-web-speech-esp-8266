#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char* ssid     = "SSID";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "PASSWORD";     // The password of the Wi-Fi network

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
    server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
    server.on("/on", HTTP_GET, on);     // Call the 'handleRoot' function when a client requests URI "/"
    server.on("/off", HTTP_GET, off);     // Call the 'handleRoot' function when a client requests URI "/"
    server.begin();                           // Actually start the server
}

void loop() { 
    server.handleClient();
  }

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
