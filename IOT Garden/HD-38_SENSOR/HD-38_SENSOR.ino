/*Includes*/
//For OLED display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ezButton.h>

/*Defines*/
#define SCL A5
#define SDA A4
#define SMSensor A1
#define BTN_CALLIBRATION_DRY 2
#define BTN_CALLIBRATION_WET 3

//OLED screen size
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

/*Constatns*/
int soilMoistureValue;
int soilMoisturePercent;
//Based on calibration of sensor
int DryValue = 534;
int WetValue = 203;


/*Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//EzButton
ezButton button(BTN_CALLIBRATION_WET);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.display();

  //Buttons
  pinMode(BTN_CALLIBRATION_DRY, INPUT);
  pinMode(BTN_CALLIBRATION_WET, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int soilMoistureValue = analogRead(A1);

  soilMoistureValue = analogRead(SMSensor);
  soilMoisturePercent = map(soilMoistureValue, DryValue, WetValue, 0, 100);
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);
  
  Serial.print("Moisture value: ");
  Serial.println(soilMoistureValue);
  Serial.print("Dry value: ");
  Serial.println(DryValue);
  Serial.print("Wet value: ");
  Serial.println(WetValue);

  if(digitalRead(BTN_CALLIBRATION_WET)==HIGH){
      WetValue=analogRead(SMSensor);
      // Wet value
      printOLED(35, "WET V", 30, String(WetValue) + "M", 3000);
  }

  if(digitalRead(BTN_CALLIBRATION_DRY)==HIGH){
      DryValue=analogRead(SMSensor);
      // Dry value
      printOLED(35, "DRY V", 30, String(DryValue) + "M", 3000);
    }
      
  // Moisture
  printOLED(35, "MOIST", 30, String(soilMoisturePercent) + "%", 2000);
  // Moisture
  printOLED(35, "MOIST", 30, String(soilMoistureValue) + "M", 2000);
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
