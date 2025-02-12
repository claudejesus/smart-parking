#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <ESP32Servo.h>

void manualUpdate();
void openGate();
void closeGate();
void lcdDisplay();
void checkWiFi();
void vehicleEntry();
void connectToWiFi();
void getDataFromGoogleSheets();
void sendDataToGoogleSheets(int availableSpaces);




// WiFi Credentials
const char* ssid = "Wokwi-GUEST";        
const char* password = ""; 

// Google Sheets API Endpoint (Replace with your actual script URL)
const char* googleScriptURL = "https://script.google.com/macros/s/AKfycbxB70-rNP4CHAI6cyEdnA9Myt0DUrzrJmraGpMSw3aRzZykynLfxaPgkMYH26qnSsyM/exec";

// Pin Definitions
#define ENTRY_BUTTON 26    
#define EXIT_BUTTON 27     
#define MANUAL_BUTTON 14   
#define LED_GATE 12      
#define SERVO_PIN 15       

int totalSpaces = 10;
int availableSpaces = 10;


Servo gateServo;
LiquidCrystal lcd(21, 19, 18, 5, 17, 16);  

void setup() {
    Serial.begin(115200);
    
    pinMode(ENTRY_BUTTON, INPUT_PULLUP);
    pinMode(EXIT_BUTTON, INPUT_PULLUP);
    pinMode(MANUAL_BUTTON, INPUT_PULLUP);
    pinMode(LED_GATE, OUTPUT);

    gateServo.attach(SERVO_PIN, 500, 2500);

    lcd.begin(16, 2);
    lcdDisplay();

    connectToWiFi();
    getDataFromGoogleSheets();  // Initialize availableSpaces from the sheet
}

void loop() {
    checkWiFi();

    if (digitalRead(ENTRY_BUTTON) == LOW) {
        delay(200);
        vehicleEntry();
    }

    if (digitalRead(EXIT_BUTTON) == LOW) {
        delay(200);
        if (availableSpaces < totalSpaces) {
        Serial.println("Vehicle Exiting...");
        availableSpaces++;

        Serial.println("Opening Gate...");
        digitalWrite(LED_GATE, HIGH);
        gateServo.write(90);
        delay(3000);
        Serial.println("Closing Gate...");
        digitalWrite(LED_GATE, LOW);
        gateServo.write(0);

        lcdDisplay();
        sendDataToGoogleSheets(availableSpaces);
    } else {
        Serial.println("No vehicles to exit!");
    }
        //getDataFromGoogleSheets();
    }

    if (digitalRead(MANUAL_BUTTON) == LOW) {
        delay(200);
        manualUpdate();
    }

    delay(500);  // Reduce CPU usage
}

// Function to connect to WiFi
void connectToWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 15) {  
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
    } else {
        Serial.println("\nWiFi Connection Failed!");
    }
}

// Function to check WiFi and reconnect if necessary
void checkWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Lost. Reconnecting...");
        connectToWiFi();
    }
}

// Function to send data to Google Sheets (POST)
void sendDataToGoogleSheets(int availableSpaces) {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient http;
        String postData = "spaces=" + String(availableSpaces);

        Serial.println("Sending data to Google Sheets...");
        http.begin(client, googleScriptURL);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        int httpResponseCode = http.POST(postData);
        Serial.print("HTTP Response Code: ");
        Serial.println(httpResponseCode);

        if (httpResponseCode > 0) {
            Serial.println("Data sent successfully!");
        } else {
            Serial.println("Failed to send data.");
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected! Data not sent.");
    }
}

// Function to GET data from Google Sheets
void getDataFromGoogleSheets() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient http;
        String requestURL = String(googleScriptURL) + "?action=get";

        Serial.println("Fetching data from Google Sheets...");
        http.begin(requestURL);
        
        int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.print("Google Sheets Response: ");
            Serial.println(response);
            availableSpaces = response.toInt();  // Update available spaces
            lcdDisplay();
        } else {
            Serial.print("Error in GET request: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected! Data not retrieved.");
    }
}

void vehicleEntry() {
    if (availableSpaces > 0) {
        Serial.println("Vehicle Entering...");
        availableSpaces--;

        openGate();
        delay(3000);
        closeGate();

        lcdDisplay();
        sendDataToGoogleSheets(availableSpaces);
    } else {
        Serial.println("Parking Full!");
    }
}

// void vehicleExit() {
//     // if (availableSpaces < totalSpaces) {
//     //     Serial.println("Vehicle Exiting...");
//     //     availableSpaces++;

//     //     openGate();
//     //     delay(3000);
//     //     closeGate();

//     //     lcdDisplay();
//     //     sendDataToGoogleSheets(availableSpaces);
//     // } else {
//     //     Serial.println("No vehicles to exit!");
//     // }
// }

void manualUpdate() {
    Serial.println("Manual Update: Reset to 10 spaces.");
    availableSpaces = totalSpaces;
    lcdDisplay();
    sendDataToGoogleSheets(availableSpaces);
}

void openGate() {
    Serial.println("Opening Gate...");
    digitalWrite(LED_GATE, HIGH);
    gateServo.write(90);
}

void closeGate() {
    Serial.println("Closing Gate...");
    digitalWrite(LED_GATE, LOW);
    gateServo.write(0);
}

void lcdDisplay() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Parking System");
    lcd.setCursor(0, 1);
    lcd.print("Spaces: ");
    lcd.print(availableSpaces);
}
