public class Serialcomunication extends Grafico {
  String dati = " ";
  String valore="";
  char dativec; 
  int index = 0;
  public long ti=0; 
public long ti2=0; 


 int y2=95, y4=245;
  public Serialcomunication() {
  }

  void serialsend() {
    if (mousePressed) {
      if (millis()-ti>500) {
        if (pulsante==true) {
          if (mousePressed && mouseY < y2+20) {
            float pinzamap=map(target1, 50, 350, 0, 180);
            String pinza="P"+str(pinzamap);
            MyPort.write(pinza);
            println(pinza);
          }
        }

        ti=millis();
      }
      if (millis()-ti2>500) {
        if (pulsante==true) {
          if (mousePressed && mouseY > y4-20) {
            float rotazmap=map(target2, 50, 350, -90, 90);
            String rotaz="R"+ str(rotazmap);
            MyPort.write(rotaz);
            println(rotaz);
          }
        }
        ti2=millis();
      }
      //println(rotaz);
    }
  }

  void serialreceive() {
    if (MyPort.available() > 0) {
      dati = MyPort.readStringUntil('\n');
      dati=dati.trim();
    }
    //  println(dati);
    dativec=dati.charAt(0);

    if (dativec == 'T') {
      //   print("Temperature: ");
      valore = "";
      for (int i = 1; i < dati.length(); i++) {
        valore = valore +dati.charAt(i) ;
      }
      tempC = float(valore);
      //   println(tempC);
    }

    if (dativec == 'A') {
      //   print("Angle: ");
      valore = "";
      for (int i = 1; i < dati.length(); i++) {
        valore = valore +dati.charAt(i) ;
      }
      Incl = float(valore);
      //   println(Incl);
    }
    if (dativec == 'B') {
      //    print("BPM: ");
      valore = "";
      for (int i = 1; i < dati.length(); i++) {
        valore = valore +dati.charAt(i) ;
      }
      Batt = float(valore);
      //   println(Batt);
    }
    if (dativec == 'M') {
      //   print("average: ");
      valore = "";
      for (int i = 1; i < dati.length(); i++) {
        valore = valore +dati.charAt(i) ;
      }
      if (int(valore)<0) {
        valore="1023";
      }
      if (index<data.length) {
        //data[index]=float(valore);
        data[index]=map(float(valore), 0, 1024, 0, 300);
        index++;
      } else if (index==data.length) {
        index=0;
        data[index]=map(float(valore), 0, 1024, 0, 300);
      }
      //  println(valore) ;
      // println(datax);
    }
  }
}
