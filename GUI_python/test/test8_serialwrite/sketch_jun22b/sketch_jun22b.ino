void setup() {
  Serial.begin(9600);
}

void loop() {

  for (int i = 0; i < 1000; i++)
  {
    Serial.print("T");
    Serial.println("25");
    Serial.print("A");
    Serial.println("70");
    Serial.print("M");
    Serial.println(String(i));
    Serial.print("B");
    Serial.println("90");
    Serial.print("S");
    Serial.println("400");
    delay(500);
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

}
