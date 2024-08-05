#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// Pin where the DHT11 is connected
#define DHTPIN 5

// DHT 11
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char* ssid = "Mechi Campus";
const char* password = "";

// Create a server listening on port 80
ESP8266WebServer server(80);

// Function to handle the root route
void handleRoot() {
  // Read temperature and humidity from the DHT sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Create the HTTP response
  String response = "<!DOCTYPE HTML>\r\n<html>\r\n";
  response += "<head>\r\n";
  response += "<meta http-equiv='refresh' content='5'>\r\n";
  response += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css'>\r\n";
  response += "<style>\r\n";
  response += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; padding: 50px; }\r\n";
  response += ".container { display: inline-block; background: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }\r\n";
  response += ".icon { font-size: 50px; margin: 20px 0; }\r\n";
  response += ".temperature { color: #ff6347; }\r\n"; // Tomato color
  response += ".humidity { color: #1e90ff; }\r\n"; // DodgerBlue color
  response += "</style>\r\n";
  response += "</head>\r\n";
  response += "<body>\r\n";
  response += "<div class='container'>\r\n";
  response += "<h1>Temperature and Humidity</h1>\r\n";
  response += "<div class='temperature'>\r\n";
  response += "<i class='fas fa-thermometer-half icon'></i>\r\n";
  response += "<p>Temperature: " + String(t) + " °C</p>\r\n";
  response += "</div>\r\n";
  response += "<div class='humidity'>\r\n";
  response += "<i class='fas fa-tint icon'></i>\r\n";
  response += "<p>Humidity: " + String(h) + " %</p>\r\n";
  response += "</div>\r\n";
  response += "</div>\r\n";
  response += "<script>setTimeout(() => { location.reload(); }, 5000);</script>\r\n";
  response += "</body>\r\n</html>\r\n";

  // Send the response to the client
  server.send(200, "text/html", response);
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  
  // Initialize the DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define the handling function for the root path
  server.on("/", handleRoot);

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
