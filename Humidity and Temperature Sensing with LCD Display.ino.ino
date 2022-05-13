#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

// Button variables
const int buttonPin = 23;
int buttonState = 0;

// LED Pin variables
int bluePin = 13;
int greenPin = 12;
int redPin = 2;
bool isLit = false;

// LCD variables
int rs = 8;
int en = 9;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// DHT11 variables
#define DHTPIN 10
#define DHTTYPE DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  // Button pin setup
  pinMode(buttonPin, INPUT);

  // LED pin setup
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  dht.begin();
  lcd.begin(16, 2);

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  sensors_event_t event;

  int buttonState = digitalRead(buttonPin);

  // Check for light toggle
  if (buttonState == HIGH && isLit == false) {
    isLit = true;
  } else if (buttonState == HIGH && isLit == true) {
    isLit = false;
  }

  lcd.clear();
  // Display humidity
  dht.humidity().getEvent(&event);
  lcd.setCursor(0, 0);
  lcd.print("Humi:" + String(event.relative_humidity, 0) + "%");

  int currentHumi = (int) event.relative_humidity;

  // I tried a switch statement first, don't judge me!

  // Set color based on humidity value
  if (isLit == true) {
    if (currentHumi <= 15) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 100);
      analogWrite(bluePin, 0);
    } else if (currentHumi <= 40) {
      analogWrite(redPin, 255);
      analogWrite(greenPin, 207);
      analogWrite(bluePin, 77);
    } else if (currentHumi <= 60) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
    } else if (currentHumi >= 70) {
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
    }
  } else {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
  // Display temperature
  dht.temperature().getEvent(&event);
  lcd.setCursor(0, 1);
  lcd.print("Temp:" + String(event.temperature, 0) + "C");

  lcd.setCursor(11, 0);
  lcd.print("L:");
  lcd.setCursor(13, 0);
  lcd.print(isLit == false ? "Off" : "On");

  // Countdown display
  delay(1000);

  lcd.setCursor(13, 1);
  lcd.print('.');
  delay(1000);

  lcd.setCursor(14, 1);
  lcd.print('.');
  delay(1000);

  lcd.setCursor(15, 1);
  lcd.print('.');
  delay(1000);

}
