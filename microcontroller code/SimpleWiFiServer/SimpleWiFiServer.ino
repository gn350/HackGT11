/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/
#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "Scream";
const char* password = "Samyukta123!";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Data to be stored
float position[3] = {10.0, 2.0, 4.0};   // x, y, z position
float acceleration[3] = {6.0, -2.0, -8.0}; // x, y, z acceleration
uint8_t scream = 100;

// Convert data to JSON for GET request
String getDataJSON() {
  DynamicJsonDocument doc(256);
  doc["position"]["x"] = position[0];
  doc["position"]["y"] = position[1];
  doc["position"]["z"] = position[2];
  doc["acceleration"]["x"] = acceleration[0];
  doc["acceleration"]["y"] = acceleration[1];
  doc["acceleration"]["z"] = acceleration[2];
  doc["scream"] = scream;

  String jsonString;
  serializeJson(doc, jsonString);
  return jsonString;
}

// Handle POST request to update data
void updateDataFromJSON(String json) {
  DynamicJsonDocument doc(256);
  deserializeJson(doc, json);

  position[0] = doc["position"]["x"];
  position[1] = doc["position"]["y"];
  position[2] = doc["position"]["z"];
  acceleration[0] = doc["acceleration"]["x"];
  acceleration[1] = doc["acceleration"]["y"];
  acceleration[2] = doc["acceleration"]["z"];
  scream = doc["scream"];
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Route to handle GET requests to retrieve data
  server.on("/get_data", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = getDataJSON();
    request->send(200, "application/json", json);
  });

  // Route to handle POST requests to update data
  server.on("/set_data", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("body", true)) {
      String body = request->getParam("body", true)->value();
      Serial.print(body);
      updateDataFromJSON(body);
      request->send(200, "application/json", "{\"message\":\"Data updated\"}");
    } else {
      request->send(400, "application/json", "{\"message\":\"Bad Request\"}");
    }
  });

  // Start server
  server.begin();
}

void loop() {
  // Nothing in the loop as the server is asynchronous
}

/*
// Load Wi-Fi library
#include <WiFi.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid     = "Scream";
const char* password = "Samyukta123!";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){

  // // JSON file stuff
  // // Check if data is available to read
  // if (Serial.available() > 0) {
  //   // Create a buffer to hold the incoming JSON string
  //   String jsonString = Serial.readStringUntil('\n'); // read until newline

  //   // Create a JSON document
  //   StaticJsonDocument<200> doc; // Adjust size based on your JSON structure

  //   // Deserialize the JSON string
  //   DeserializationError error = deserializeJson(doc, jsonString);

  //   // Check for errors
  //   if (error) {
  //     Serial.print(F("deserializeJson() failed: "));
  //     Serial.println(error.f_str());
  //     return;
  //   }

  //   // Extract the integer value from the JSON
  //   int myInteger = doc["myKey"]; // Replace "myKey" with the actual key

  //   // Print the extracted integer
  //   Serial.print(F("Extracted integer: "));
  //   Serial.println(myInteger);
  // }

  // Webserver stuff
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>GPIO 5 - State " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>GPIO 4 - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
*/