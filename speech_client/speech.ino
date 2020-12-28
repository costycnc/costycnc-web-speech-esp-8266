/*
 * ESP8266 NodeMCU LED Control over WiFi Demo
 *
 * https://circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>

//---------------------------------------------------------------
/*Our HTML webpage contents in program memory
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>WiFi LED on off demo: 1</h1><br>
Ciclk to turn <a href="ledOn">LED ON</a><br>
Ciclk to turn <a href="ledOff">LED OFF</a><br>
<hr>
<a href="https://circuits4you.com">circuits4you.com</a>
</center>

</body>
</html>
)=====";
*/
/*
String s="<!DOCTYPE html><html><body><center>"
"<h1>WiFi LED on off demo: 1</h1><br>"
"Ciclk to turn <a href=\"ledOn\">LED ON</a><br>"
"Ciclk to turn <a href=\"ledOff\">LED OFF</a><br>"
"<hr><a href=\"https://circuits4you.com\">circuits4you.com</a></center>"
"</body></html>";
*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

String s="<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\" />"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />"
    "<meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\" /><title>Speech Recognition</title><style>"
    "body { background-color: orangered;}"
   ".words {width: 300px;height: auto;margin: 50px auto; background-color: #fff;padding: 25px;}"
  "</style></head>"
  "<body><div class=\"words\"></div>"
  "<script>"
  "const words = document.querySelector('.words');"
"let p = document.createElement('p');"
"words.appendChild(p);"
    "var xhttp = new XMLHttpRequest();"
     "window.SpeechRecognition =window.SpeechRecognition || window.webkitSpeechRecognition;"
"const recognition = new SpeechRecognition();"
"recognition.interimResults = true;"
"recognition.lang = 'en-EN';"
"recognition.addEventListener('result', e => {"
  "const transcript = Array.from(e.results)"
    ".map(result => result[0].transcript)"
    ".join('');"
  "p.textContent = transcript;"
  "if (e.results[0].isFinal) {"
    "p = document.createElement('p');"
    "words.appendChild(p);"
   "if (transcript.includes('еркебулан')) { console.log('+unicorn');}"
    "if (transcript.includes('on')) {console.log('+on');xhttp.open('GET', '/on', true);xhttp.send();}"
    "if (transcript.includes('off')) {console.log('+off');xhttp.open('GET', '/off', true);xhttp.send();}"
  "}});"
"recognition.addEventListener('end', recognition.start);recognition.start();"
 " </script></body></html>";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++





//---------------------------------------------------------------
//On board LED Connected to GPIO2
#define LED 2  

//SSID and Password of your WiFi router
const char* ssid = "Wind3 HUB-315F35";
const char* password = "costycnccostycnc";

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 Serial.println("You called root page");
 //String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleon() { 
 Serial.println("LED on page");
 digitalWrite(LED,LOW); //LED is connected in reverse
 server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
 server.send(303);
}

void handleoff() { 
 Serial.println("LED off page");
 digitalWrite(LED,HIGH); //LED off
 server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED,OUTPUT); 
  //Power on LED state off
  digitalWrite(LED,HIGH);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/on", handleon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/off", handleoff);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
