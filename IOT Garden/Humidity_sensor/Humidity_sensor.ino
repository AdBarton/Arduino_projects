/*Includes*/
//For OLED display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// DHT sensor library - Version: Latest
#include <DHT.h>
#include <DHT_U.h>

/*Defines*/
#define RELAY_PIN 3
#define SCL A5
#define SDA A4
#define DHTPIN 8
#define DHTTYPE DHT22

// Analog input port
#define SENSOR_IN 0

//OLED screen size
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

/*Constatns*/
bool pump_status = false;
int pump_trigger = 70;
int soilMoistureValue;
int soilMoisturePercent;
float temp;
float hum;
//Based on calibration of sensor
const int DryValue = 534;
const int WetValue = 203;


/*Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

/*Setup*/
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.display();

  // Initialize DHT22
  dht.begin();

  //Pump off
  pumpOff();
}

/*Loop*/
void loop() {
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  soilMoistureValue = analogRead(SENSOR_IN);
  soilMoisturePercent = map(soilMoistureValue, DryValue, WetValue, 0, 100);
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Moisture value: ");
  Serial.println(soilMoistureValue);

  checkSoilMoistureValue();

  // Cycle values on OLED Display
  // Temperature
  printOLED(35, "TEMP", 10, String(temp) + "C", 2000);
  // Humidity
  printOLED(30, "HUMID", 10, String(hum) + "%", 2000);
  // Moisture
  printOLED(35, "MOIST", 30, String(soilMoisturePercent) + "%", 2000);
  // Moisture
  printOLED(35, "MOIST", 30, String(soilMoistureValue) + "M", 2000);
}

void checkSoilMoistureValue(){
  if(soilMoisturePercent<= pump_trigger){
      pumpOn();
      delay(2000);
      pumpOff();
    }
}

/*
 * Pump goes on
 */
void pumpOn() {
  // Turn pump on
  digitalWrite(RELAY_PIN, LOW);
  pump_status=true;
}

/*
 * Pump goes off
 */
void pumpOff() {
  // Turn pump off
  digitalWrite(RELAY_PIN, HIGH);
  pump_status=false;
}

/*
 * Print OLED display
 */
void printOLED(int top_cursor, String top_text, int main_cursor, String main_text, int delay_time){
  display.setCursor(top_cursor, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(top_text);

  display.setCursor(main_cursor, 40);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(main_text);
  display.display();

  delay(delay_time);
  display.clearDisplay();
 
}
