#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "Scream";
const char* password = "Samyukta123!";

// Initialize the server on port 80
WebServer server(80);

// Array to store the seven variables
int data[7] = {1, 2, 3, 4, 5, 6, 7};  // [pos_x, pos_y, pos_z, accel_x, accel_y, accel_z, scream]

// Function to handle GET requests
void handleGet() {
  StaticJsonDocument<200> jsonDoc;

  // Add the first six elements of the array to the JSON response
  jsonDoc["position"]["x"] = data[0];
  jsonDoc["position"]["y"] = data[1];
  jsonDoc["position"]["z"] = data[2];
  jsonDoc["acceleration"]["x"] = data[3];
  jsonDoc["acceleration"]["y"] = data[4];
  jsonDoc["acceleration"]["z"] = data[5];

  String response;
  serializeJson(jsonDoc, response);
  
  server.send(200, "application/json", response);
}

// Function to handle POST requests
void handlePost() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");

    // Parse the JSON data received
    StaticJsonDocument<100> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, body);
    
    if (error) {
      server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }
    
    // Update the 7th variable in the array (scream)
    if (jsonDoc.containsKey("scream")) {
      data[6] = jsonDoc["scream"];
      server.send(200, "application/json", "{\"message\":\"Scream updated\"}");
    } else {
      server.send(400, "application/json", "{\"error\":\"Missing scream key\"}");
    }
  } else {
    server.send(400, "application/json", "{\"error\":\"No data in POST request\"}");
  }
}

// Function to handle not found
void handleNotFound() {
  server.send(404, "application/json", "{\"error\":\"Not found\"}");
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    Serial.println(WiFi.localIP());
  }
  Serial.println("Connected to WiFi!");

  // Start the web server
  server.on("/get_data", HTTP_GET, handleGet);   // Handle GET requests
  server.on("/set_data", HTTP_POST, handlePost); // Handle POST requests
  server.onNotFound(handleNotFound);             // Handle unknown requests

  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient(); // Listen for client connections
}