#include <WiFi.h>

const char *ssid = "WalkingFrenchFry";
const char *password = "grace123";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client

    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte
        Serial.write(c);            // print it out the serial monitor
        
        if (c == '\n') {            // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // Send HTTP response headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // The content of the HTTP response
            client.println("Send an integer with a URL like /send?value=42<br>");
            client.println("Example: <a href=\"/send?value=42\">Send 42</a><br>");

            // The HTTP response ends with another blank line:
            client.println();
            break;
          } else {
            // Check if the current line contains the integer value
            if (currentLine.startsWith("GET /send?value=")) {
              String valueString = currentLine.substring(16); // Get the value after 'value='
              int value = valueString.toInt(); // Convert to integer
              Serial.print("Received integer: ");
              Serial.println(value);
            }

            // Clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
