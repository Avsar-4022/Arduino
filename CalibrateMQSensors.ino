#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ2_PIN A0
#define MQ135_PIN A1

float previous_R0_MQ2 = 0;
float previous_R0_MQ135 = 0;

float calculateR0(int pin) {
  float sensorValue = 0;
  for (int x = 0; x < 500; x++) {
    sensorValue += analogRead(pin);
  }
  sensorValue = sensorValue / 500.0;
  float sensorVolt = sensorValue * (5.0 / 1023.0);
  if (sensorVolt == 0) {
    Serial.println("Error: sensorVolt is zero, check sensor connections.");
    return -1; // Return an invalid value to indicate an error
  }
  float RS_air = ((5.0 * 10.0) / sensorVolt) - 10.0;
  return RS_air / 4.4;
}

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float current_R0_MQ2 = calculateR0(MQ2_PIN);
  float current_R0_MQ135 = calculateR0(MQ135_PIN);

  float average_R0_MQ2 = (previous_R0_MQ2 + current_R0_MQ2) / 2;
  float average_R0_MQ135 = (previous_R0_MQ135 + current_R0_MQ135) / 2;

  Serial.println("------ R0 Values ------");

  Serial.print("Previous R0_MQ2 = ");
  Serial.println(previous_R0_MQ2);
  Serial.print("Current R0_MQ2 = ");
  Serial.println(current_R0_MQ2);
  Serial.print("Average R0_MQ2 = ");
  Serial.println(average_R0_MQ2);

  Serial.print("Previous R0_MQ135 = ");
  Serial.println(previous_R0_MQ135);
  Serial.print("Current R0_MQ135 = ");
  Serial.println(current_R0_MQ135);
  Serial.print("Average R0_MQ135 = ");
  Serial.println(average_R0_MQ135);

  previous_R0_MQ2 = current_R0_MQ2;
  previous_R0_MQ135 = current_R0_MQ135;

  delay(5000);
}