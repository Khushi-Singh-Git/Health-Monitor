/*
   KHUSHI SINGH
   VIT,Vellore
*/


#include <DFRobot_MAX30102.h>
#include <math.h>
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <Adafruit_SSD1306.h>// For OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DFRobot_MAX30102 particleSensor;
WiFiClient client;// creating object for wifi access
const char* ssid = "**********";       // Your WiFi Id
const char* password = "***********"; //Your Network Password
unsigned long myChannelNumber = **************; //Your Channel Number for Distance (Without Brackets)
const char * myWriteAPIKey = "*********";   // YOUR_API_KEY for channel KGQPNULVCJ8DVRVH

int sensorPin = A0; // Analog Pin where the S is connected to
long HrtRate = 0; // Heart rate (determined)
long Cal_hrt_rate = 0; // calibrated heart rate
//
int32_t SPO2; //SPO2
int8_t SPO2Valid; //Flag to display if SPO2 calculation is valid
int32_t heartRate; //Heart-rate
int8_t heartRateValid; //Flag to display if heart-rate calculation is valid

void setup() {

  Serial.begin(115200);
  while (!particleSensor.begin()) {
  Serial.println("MAX30102 was not found");
 }

  delay(4000);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }
  delay(1000);
  // Display Project details
  welcome();
  delay(3000);
  productinfo();
  delay(3000);

  // Connect to WiFi network
 WiFi.begin(ssid, password);
 ThingSpeak.begin(client);
// Display connection to OLED
  display.clearDisplay();
  display.setCursor(10, 10);
  display.println("Connected to WiFi");
  display.display();
  delay(2000);
  
  display.clearDisplay();
  delay(100);
  display.setCursor(10, 10);
  display.println("GETTING SENSOR DATA");
  display.display();
}

void loop()
{
  particleSensor.heartrateAndOxygenSaturation(/**SPO2=*/&SPO2, /**SPO2Valid=*/&SPO2Valid, /**heartRate=*/&heartRate, /**heartRateValid=*/&heartRateValid);
  display.setCursor(0, 5);
  display.println("HEART RATE:");
  display.setCursor(75, 5);
  display.println("BPM");
  display.setCursor(0, 20);
  display.println("SPO2:");
  display.setCursor(75, 20);
  display.println("%");
  display.display();
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); //Update in ThingSpeak
  delay(1000);

}// loop closed


void productinfo()
{
  display.clearDisplay();
  delay(100);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println("HEART RATE & SPO2");
  display.setCursor(10, 17);
  display.println("MONITORING SYSTEM ");
  display.display();
  delay(3000);
  display.clearDisplay();
  delay(100);
   }
