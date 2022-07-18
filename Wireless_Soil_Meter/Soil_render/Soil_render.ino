/*Includes*/
//For OLED display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

/*Defines*/
#define SCL A5
#define SDA A4

//OLED screen size
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
int soilMoisturePercent;

/*Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
SoftwareSerial HC12(10, 11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HC12.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.display();
}

void loop() {
  
  while (HC12.available()) {
    soilMoisturePercent=HC12.read();
    Serial.println(String(HC12.read())); 
  } 
  // Moisture
  printOLED(35, "MOIST", 30, String(soilMoisturePercent) + "%");
}

/*
 * Print OLED display
 */
void printOLED(int top_cursor, String top_text, int main_cursor, String main_text){
  display.clearDisplay();
  display.setCursor(top_cursor, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(top_text);

  display.setCursor(main_cursor, 40);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(main_text);
  display.display();
 
}
