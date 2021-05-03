#include "serialreceive.h"
#include "dhtread.h"
#include "wifidata.h"

void setup() {
  Serial.begin(9600); // inizializza seriale per Arduino
  Esp_serial.begin(9600); // Inizializza SoftwareSerial per collegamento con ESP
  dht.begin();
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

}

void loop() {

  letturadht();

  servercall();

  decodeserial();


  delay(1);
}
