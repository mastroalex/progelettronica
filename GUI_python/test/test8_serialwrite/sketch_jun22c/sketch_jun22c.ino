void setup() {
  Serial.begin(9600);
}

void loop() {
    Serial.print("Prova");
    delay(100);
    if (Serial.available()) {
      String a = Serial.readString();
      for (int i = 0; i < 100; i++) {
          Serial.println(a);
    }
//      if (a == "C1") {
//        for (int i = 0; i < 100; i++) {
//          Serial.println("RICEVUTO C1");
//        }
//      }
//       if (a == "C0") {
//        for (int i = 0; i < 100; i++) {
//          Serial.println("RICEVUTO C0");
//        }
//      }
    }
  

}
