#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// LED pin
#define LEDPIN 2

// WiFi credentials
const char* ssid = "Mechi Campus";
const char* password = "";

// Create a server listening on port 80
ESP8266WebServer server(80);

// Current LED state
bool ledState = LOW;

// Function to handle the root route
void handleRoot() {
  // Create the HTTP response
  String response = "<!DOCTYPE HTML>\r\n<html>\r\n";
  response += "<head>\r\n";
  response += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css'>\r\n";
  response += "<style>\r\n";
  response += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; padding: 50px; }\r\n";
  response += ".container { display: inline-block; background: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }\r\n";
  response += ".button { padding: 10px 20px; font-size: 16px; color: #fff; background-color: #007BFF; border: none; border-radius: 5px; cursor: pointer; }\r\n";
  response += ".button:hover { background-color: #0056b3; }\r\n";
  response += "</style>\r\n";
  response += "</head>\r\n";
  response += "<body>\r\n";
  response += "<div class='container'>\r\n";
  response += "<h1>LED Control</h1>\r\n";
  response += "<p>LED is " + String((ledState == HIGH) ? "ON" : "OFF") + "</p>\r\n";
  response += "<button class='button' onclick='toggleLED()'>Toggle LED</button>\r\n";
  response += "</div>\r\n";
  response += "<script>\r\n";
  response += "function toggleLED() {\r\n";
  response += "  var xhttp = new XMLHttpRequest();\r\n";
  response += "  xhttp.open('GET', '/toggleLED', true);\r\n";
  response += "  xhttp.send();\r\n";
  response += "}\r\n";
  response += "setTimeout(() => { location.reload(); }, 5000);\r\n";
  response += "</script>\r\n";
  response += "</body>\r\n</html>\r\n";

  // Send the response to the client
  server.send(200, "text/html", response);
}

// Function to handle LED toggle
void handleToggleLED() {
  // Toggle the LED state
  ledState = !ledState;
  digitalWrite(LEDPIN, ledState);
  // Send a plain text response indicating the LED has been toggled
  server.send(200, "text/plain", "LED Toggled");
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Set the LED pin as output
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, ledState);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define the handling function for the root path
  server.on("/", handleRoot);

  // Define the handling function for the toggleLED path
  server.on("/toggleLED", handleToggleLED);

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Handle client requests
  server.handleClient();
}
