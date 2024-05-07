#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define DHTPIN 6         // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     // DHT 11 sensor type
DHT dht(DHTPIN, DHTTYPE);
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET); //OLED Wire SDA to A4 and SCL to A5
String airQualityString ="No Reading";
const int airQualityIntPin = A3; // Air Quality Sensor Pin

void setup() {
  
  Serial.begin(9600);
  dht.begin();
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Reading...");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  
  delay(2000);  // Wait for 2 seconds between measurements
  
  float temperatureC = dht.readTemperature();  // Read temperature in Celsius
  float humidity = dht.readHumidity();        // Read humidity in percent
  int airQualityInt = analogRead(airQualityIntPin);
  // Check if any reads failed and exit if so
  if (isnan(temperatureC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT Temp sensor!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temperature Error");
    display.display();
    return;
  }
  if (isnan(airQualityInt)) {
    Serial.println("Failed to read from Air Quality sensor!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Air Quality Error");
    display.display();
    return;
  }
  else{
    if(airQualityInt<190) {
      airQualityString = "Good";
    }
    else if(airQualityInt>189 && airQualityInt<250) {
      airQualityString = "Poor";
    }
    else if(airQualityInt>249 && airQualityInt<350) {
      airQualityString = "Bad";
    }
    else {airQualityString = "OOPSXX";}
  }

  // Convert Celsius to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

   // Update OLED display with current LED and score
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.println(temperatureF);
  
  display.setCursor(0, 12);
  display.print("Humidity: ");
  display.print(humidity);
  display.print("%");

  display.setCursor(0, 24);
  display.print("Quality: ");
  display.print(airQualityString);
  display.print(" | ");
  display.print(airQualityInt);
  display.display();

}
