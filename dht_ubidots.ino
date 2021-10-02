#include <DHT.h>
#include <UbidotsMicroESP8266.h>

#define DHTPIN 4
#define DHTTYPE DHT11

char auth[] = "BBFF-pFqxCCfq7rFw4agIW7pcAfKqVMp2H3"; // token yang dikirim dari blynk ke email masing masing
char ssid[] = "AndroidAP3F5F";
char pass[] = "safwan030804";

DHT dht(DHTPIN, DHTTYPE);
Ubidots client(auth); // setting token client di ubidots
unsigned long last = 0; // 0 detik

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); // dht mulai membaca suhu dan kelembapan
  delay(20); // delay 0,02 detik
  client.wifiConnection(ssid, pass); // menyambung ubidots client dengan wifi

}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - last > 10000) { // jika sudah 10 detik

    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis(); // 11
    client.add("kelembapan", hum); // ubidots client membaca kelembapan
    client.add("Temperatur", temp); // ubidots client membaca temperatur
    client.sendAll(true);

  }

}
