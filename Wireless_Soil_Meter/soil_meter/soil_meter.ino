#include <SoftwareSerial.h>

#define SMSensor A1

/*Constatns*/
int soilMoistureValue;
int soilMoisturePercent;

//Based on calibration of sensor
int DryValue = 1023;
int WetValue = 136;

SoftwareSerial HC12(10, 11);

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
}

void loop() {
  while (HC12.available()) {
    Serial.write(HC12.read());
  }
  while (Serial.available()) {
    HC12.write(Serial.read());
  }

    // put your main code here, to run repeatedly:
  int soilMoistureValue = analogRead(SMSensor);

  soilMoistureValue = analogRead(SMSensor);
  soilMoisturePercent = map(soilMoistureValue, DryValue, WetValue, 0, 100);
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);
  
  HC12.write(soilMoisturePercent);
  
  Serial.print("Moisture (perecent): ");
  Serial.println(soilMoisturePercent);
  
  Serial.print("Moisture: ");
  Serial.println(soilMoistureValue);

  Serial.print("Moisture dry: ");
  Serial.println(DryValue);
  
  Serial.print("Moisture wet: ");
  Serial.println(WetValue);
}
