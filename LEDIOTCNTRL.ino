#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "PUT YOUR NETWORK ID";
const char* password = "NETWORK PASSWWORD";

// Set GPIO pins for LEDs
const int ledPin1 = D1;
const int ledPin2 = D2;

// Create an instance of the server
ESP8266WebServer server(80);

void setup() {
  // Initialize the LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Begin serial communication at a baud rate of 115200
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  
  // Define web server routes
  server.on("/", handleRoot);
  server.on("/on1", handleOn1);
  server.on("/off1", handleOff1);
  server.on("/on2", handleOn2);
  server.on("/off2", handleOff2);
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}

void handleRoot() {
  String html = "<html>\
                  <head>\
                    <title>LED Control</title>\
                  </head>\
                  <body>\
                    <h1>Control LEDs</h1>\
                    <h2>LED 1</h2>\
                    <a href=\"/on1\"><button>Turn On</button></a>\
                    <a href=\"/off1\"><button>Turn Off</button></a>\
                    <h2>LED 2</h2>\
                    <a href=\"/on2\"><button>Turn On</button></a>\
                    <a href=\"/off2\"><button>Turn Off</button></a>\
                  </body>\
                </html>";
  server.send(200, "text/html", html);
}

void handleOn1() {
  digitalWrite(ledPin1, HIGH); // Turn LED 1 on
  //server.send(200, "text/html", "LED 1 is ON<br><a href=\"/\">Go Back</a>");
}

void handleOff1() {
  digitalWrite(ledPin1, LOW); // Turn LED 1 off
  //server.send(200, "text/html", "LED 1 is OFF<br><a href=\"/\">Go Back</a>");
}

void handleOn2() {
  digitalWrite(ledPin2, HIGH); // Turn LED 2 on
  //server.send(200, "text/html", "LED 2 is ON<br><a href=\"/\">Go Back</a>");
}

void handleOff2() {
  digitalWrite(ledPin2, LOW); // Turn LED 2 off
  server.send(200, "text/html", "LED 2 is OFF<br><a href=\"/\">Go Back</a>");
}
