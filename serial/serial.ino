#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const char* ssid = "yourssid";
const char* password = "yourpassword";

const int roomLED = 2;    // GPIO2 for Room LED
const int kitchenLED = 2; // GPIO4 for Kitchen LED

bool kitchenBlinking = false; // Flag for Kitchen LED blinking
ESP8266WebServer server(80);

String receivedPrompt = "";  

void handleRoot() {
    String html = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
            <title>Send Prompt</title>
        </head>
        <body>
            <h1>Send a Prompt</h1>
            <input type="text" id="prompt" placeholder="Enter your prompt">
            <button onclick="sendPrompt()">Send</button>

            <script>
                function sendPrompt() {
                    const prompt = document.getElementById('prompt').value;
                    fetch('/send?prompt=' + encodeURIComponent(prompt))
                        .then(response => response.text())
                        .then(data => alert(data));
                }
            </script>
        </body>
        </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

void handleSendPrompt() {
    if (server.hasArg("prompt")) {
        receivedPrompt = server.arg("prompt");
        Serial.println(receivedPrompt);  // Forward the prompt to the Python script
        server.send(200, "text/plain", "Prompt sent to Python script: " + receivedPrompt);
    } else {
        server.send(400, "text/plain", "No prompt provided");
    }
}

void setup() {
    Serial.begin(115200);  // Initialize Serial communication
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/send", handleSendPrompt);

    server.begin();
    Serial.println("HTTP server started");

    pinMode(roomLED, OUTPUT);
    pinMode(kitchenLED, OUTPUT);
    digitalWrite(roomLED, HIGH);  // Turn off LEDs initially
    digitalWrite(kitchenLED, HIGH);
    
}

void loop() {
    server.handleClient();

    if (Serial.available()) {
        char action = Serial.read();  // Read the single character response
        Serial.println("Received action: " + String(action));  // Debugging

        // Perform the corresponding LED operation
        if (action == 'A') {
            digitalWrite(roomLED, LOW);  // Turn Room LED ON
            Serial.println("Room LED ON");
        } else if (action == 'B') {
            digitalWrite(roomLED, HIGH);  // Turn Room LED OFF
            Serial.println("Room LED OFF");
        } else if (action == 'C') {
            kitchenBlinking = true;  // Start Kitchen LED blinking
            Serial.println("Kitchen LED Blinking ON");
        } else if (action == 'D') {
            kitchenBlinking = false;  // Stop Kitchen LED blinking
            digitalWrite(kitchenLED, HIGH);  // Ensure it's OFF
            Serial.println("Kitchen LED Blinking OFF");
        } else {
            Serial.println("Invalid action received.");
        }
    }

    // If Kitchen LED is blinking, toggle it every 500ms
    if (kitchenBlinking) {
        digitalWrite(kitchenLED, LOW);  // Turn Kitchen LED ON
        delay(500);
        digitalWrite(kitchenLED, HIGH); // Turn Kitchen LED OFF
        delay(500);
    }
}