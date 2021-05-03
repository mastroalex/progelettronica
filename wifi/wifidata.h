#ifndef wifidata
#define wifidata

#include "serialreceive.h"
#include "dhtread.h"
#include "sensdata.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>
#include <Hash.h>

//timer
unsigned long t2 = 0;
unsigned long dt = 0;
unsigned long t3 = 200;//update database every

void servercall () {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);    // Your Domain name with URL path or IP address with pat

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    dt = millis() - t2;
    if (dt >= t3) {
      // Prepare your HTTP POST request data
      String httpRequestData = "api_key=" + apiKeyValue + "&tempmpu=" + String(tempmpu)
                               + "&angle=" + String(angle) + "&average=" + String(average) 
                                   +  "&bpm=" + String(BPM) + "&soglia=" + String(soglia)
                                    + "&temp=" + String(t) + "&hum=" + String(h) + "";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      t2 = millis();
    }
    // Free resources
    http.end();
  }
}
#endif
