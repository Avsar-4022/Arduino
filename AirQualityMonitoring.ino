#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ2_PIN A0
#define MQ135_PIN A1

// Updated calibrated R0 values
float R0_MQ2 = -1.00; // Calibrated value for MQ-2 sensor
float R0_MQ135 = 4.00; // Calibrated value for MQ-135 sensor

float calculatePPM(int pin, float R0, float m, float b) {
  float sensorValue = analogRead(pin);
  float sensorVolt = sensorValue * (5.0 / 1023.0);
  float RS_gas = ((5.0 * 10.0) / sensorVolt) - 10.0;
  float ratio = RS_gas / R0;
  float ppm_log = (log10(ratio) - b) / m;
  return pow(10, ppm_log);
}

float convertToUGM3(float ppm, float molecularWeight) {
  return ppm * (molecularWeight / 24.45);
}

String getRemarks(float value, String type) {
  if (type == "CO") {
    if (value > 100) return "Dangerous";
    else if (value > 50) return "Very Poor";
    else if (value > 25) return "Poor";
    else if (value > 10) return "Moderate";
    else return "Good";
  } else if (type == "PM2.5") {
    if (value > 150) return "Hazardous";
    else if (value > 100) return "Very Unhealthy";
    else if (value > 55) return "Unhealthy";
    else if (value > 35) return "Moderate";
    else return "Good";
  } else if (type == "PM10") {
    if (value > 430) return "Severe";
    else if (value > 250) return "Very Poor";
    else if (value > 100) return "Poor";
    else if (value > 50) return "Moderate";
    else return "Good";
  }
  return "Unknown";
}

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  float mq2_ppm = calculatePPM(MQ2_PIN, R0_MQ2, -0.318, 1.133); // Example slope and intercept, adjust if needed
  float mq135_ppm = calculatePPM(MQ135_PIN, R0_MQ135, -0.318, 1.133); 


  

  
  float mq2_ugm3 = convertToUGM3(mq2_ppm, 30.0); // Example molecular weight for smoke
  float mq135_ugm3 = convertToUGM3(mq135_ppm, 30.0); // Use appropriate molecular weight for specific gases

  Serial.println("------ Air Quality Monitoring ------");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println("Air Quality:");
  Serial.print("CO (approx): ");
  Serial.print(mq2_ugm3);
  Serial.print(" µg/m³ - ");
  Serial.println(getRemarks(mq2_ugm3, "CO"));

  Serial.print("PM2.5 (approx): ");
  Serial.print(mq135_ugm3);
  Serial.print(" µg/m³ - ");
  Serial.println(getRemarks(mq135_ugm3, "PM2.5"));


  while (1);
}

