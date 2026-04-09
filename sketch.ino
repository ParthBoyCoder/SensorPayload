#include <DHT.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// ------------------- DHT11 -------------------
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ------------------- MQ135 -------------------
#define MQ135_PIN A0

// ------------------- HX710B -------------------
#define HX_DOUT 4
#define HX_SCK 5

long baseline_raw = 0;

// HX710B read function
long readHX710Braw() {
  unsigned long count = 0;
  while (digitalRead(HX_DOUT));

  for (int i = 0; i < 24; i++) {
    digitalWrite(HX_SCK, HIGH);
    count = (count << 1) | digitalRead(HX_DOUT);
    digitalWrite(HX_SCK, LOW);
  }

  digitalWrite(HX_SCK, HIGH);
  digitalWrite(HX_SCK, LOW);

  if (count & 0x800000) count |= 0xFF000000;

  return (long)count;
}

// ------------------- GPS -------------------
int RXPin = 2; // GPS TX → Arduino 2
int TXPin = 3; // GPS RX → Arduino 3
SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // HX710B
  pinMode(HX_SCK, OUTPUT);
  pinMode(HX_DOUT, INPUT);

  delay(300);

  long sum = 0;
  for (int i = 0; i < 40; i++) {
    sum += readHX710Braw();
    delay(5);
  }
  baseline_raw = sum / 40;

  // GPS
  gpsSerial.begin(9600);

  Serial.println("System Ready.\n");
}

void loop() {

  // ------------------- GPS Processing -------------------
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  // ------------------- DHT11 -------------------
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // ------------------- MQ135 -------------------
  int mq = analogRead(MQ135_PIN);

  // ------------------- HX710B Pressure -------------------
  long raw = readHX710Braw();
  float Pa = ((float)raw / (float)baseline_raw) * 101325.0;

  // ------------------- OUTPUT -------------------
  Serial.println("----- SENSOR DATA -----");

  Serial.print("Temp: "); Serial.print(t); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(h); Serial.println(" %");
  Serial.print("MQ135: "); Serial.println(mq);
  Serial.print("Pressure: "); Serial.print(Pa); Serial.println(" Pa");

  // GPS
  if (gps.location.isValid()) {
    Serial.print("Latitude: "); Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: "); Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: "); Serial.print(gps.altitude.meters()); Serial.println(" m");
  } else {
    Serial.println("Location: Not Available");
  }

  Serial.print("Date: ");
  if (gps.date.isValid()) {
    Serial.print(gps.date.day()); Serial.print("/");
    Serial.print(gps.date.month()); Serial.print("/");
    Serial.println(gps.date.year());
  } else Serial.println("Not Available");

  Serial.print("Time: ");
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print("0");
    Serial.print(gps.time.hour()); Serial.print(":");

    if (gps.time.minute() < 10) Serial.print("0");
    Serial.print(gps.time.minute()); Serial.print(":");

    if (gps.time.second() < 10) Serial.print("0");
    Serial.print(gps.time.second());
  } else Serial.println("Not Available");

  Serial.println("-----------------------\n");

  delay(500);
}
