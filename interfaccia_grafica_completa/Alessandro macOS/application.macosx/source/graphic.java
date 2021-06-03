import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class graphic extends PApplet {


ControlP5 cp5;

Serial MyPort;

float target1;
float target2;
PFont font24;
PFont font12;

boolean pulsante=false;

//dati comunicazione
float tempC = 0;
float Incl = 0;
float Batt=0;
float[] data; 


Termom termom= new Termom(); 
Schermo schermo=new Schermo();
Slider slider=new Slider();
Serialcomunication serialcomunication=new Serialcomunication();
Switchcommand switchcommand = new Switchcommand();
Grafico grafico = new Grafico();

public void setup()
{
  
  background(255);

  MyPort =  new Serial(this, "/dev/tty.HC-05-SerialPort", 9600);
  //MyPort.bufferUntil('\n');
  grafico.setdati();
  cp5 = new ControlP5(this);
  switchcommand.setup();
  schermo.cuore(); // inizializza l'immagine del cuore 
  slider.sliderset();
}

public void draw()
{
  //Grafico
  background(255);
  serialcomunication.serialreceive();
  grafico.assi();
  termom.disegna();
  slider.slider1();
  slider.slider2();
  schermo.temperaturadigitale(tempC);
  schermo.inclinazione(Incl);
  schermo.battito(Batt);
  serialcomunication.serialsend();
}

//icon controll
public void icon(boolean theValue) {

  println("got an event for icon", theValue);
  if (theValue == true) {
    MyPort.write("C1");
    pulsante=true;
  }  
  if (theValue == false) {
    MyPort.write("C0");
    pulsante=false;
  }
} 
public class Grafico {
public float[] datax; 
 public Grafico(){}
 
 public void setdati(){
 data = new float[1000];
  for (int i=0; i < data.length; i++) {
    data[i] = 100;
  }
  datax = new float[data.length];
  for (int i=0; i < datax.length; i++) {
    float passo=900/PApplet.parseFloat(data.length);
    datax[i] = 50+i*passo;
  }
 }
 
 public void assi(){
 for (int i=0; i<data.length-1; i++) {
    fill(55, 200, 50);
    line(datax[i], 650-data[i], datax[i+1], 650-data[i+1]);
  }


  stroke(0, 0, 250);
  strokeWeight(2);
  //line(50,800-V,950,800-V);
  stroke(0, 0, 0);
  line(50, 350, 50, 650);
  line(50, 650, 950, 650);
  fill(0, 0, 0);
  triangle(48, 350, 52, 350, 50, 340);
  triangle(940, 648, 940, 652, 950, 650);
  textSize(12);
  text("t(s)", 965, 665);
  text("V(v)", 15, 350);
 }
}
public class Schermo {
  float tempC = 0;
  float Incl = 0;
  float Batt=0; 
PImage battitook;
int  graycol=130, xshift=4, yshift=50;
  int x1=50, y1=50;




  public Schermo() {
  }
  public void cuore(){
        battitook = loadImage("battitook.png");

  }

  public void temperaturadigitale(float tempC) {
    // Rettangolo dati 
    fill(190);
    stroke(0);
    strokeWeight(1);
    rect(1200, 70, 180, 140, 7);
    fill(0, 0, 0);
    textFont(font24);
    textAlign(LEFT);
    text("Temperature", 1210, 40);
    text(" °C", 1300, 150);
    text(nfc(tempC, 1), 1250, 150);
  }

  public void inclinazione(float Incl) {

    //Rettangolo inclinazione
    fill(190);
    stroke(0);
    strokeWeight(1);
    rect(700, 70, 180, 140, 7);
    fill(0, 0, 0);
    textFont(font24);
    text("Roll", 760, 40);
    text(" °", 800, 150);
    text(nfc(Incl, 1), 770, 150);
  }
  
  public void battito (float Batt){
    //Battito
  textFont(font24); 
  fill(250, 0, 0); 
  text("BPM", x1+xshift+950, y1-10); 
  fill(0, 0, 0);
  image(battitook, x1+900, y1+20);
  text(nfc(Batt, 0), 1017, 150);
  }
}
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

  public void serialsend() {
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

  public void serialreceive() {
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
      tempC = PApplet.parseFloat(valore);
      //   println(tempC);
    }

    if (dativec == 'A') {
      //   print("Angle: ");
      valore = "";
      for (int i = 1; i < dati.length(); i++) {
        valore = valore +dati.charAt(i) ;
      }
      Incl = PApplet.parseFloat(valore);
      //   println(Incl);
    }
    if (dativec == 'B') {
      //    print("BPM: ");
      valore = "";
      for (int i = 1; i < dati.length(); i++) {
        valore = valore +dati.charAt(i) ;
      }
      Batt = PApplet.parseFloat(valore);
      //   println(Batt);
    }
    if (dativec == 'M') {
      //   print("average: ");
      valore = "";
      for (int i = 1; i < dati.length(); i++) {
        valore = valore +dati.charAt(i) ;
      }
      if (PApplet.parseInt(valore)<0) {
        valore="1023";
      }
      if (index<data.length) {
        //data[index]=float(valore);
        data[index]=map(PApplet.parseFloat(valore), 0, 1024, 0, 300);
        index++;
      } else if (index==data.length) {
        index=0;
        data[index]=map(PApplet.parseFloat(valore), 0, 1024, 0, 300);
      }
      //  println(valore) ;
      // println(datax);
    }
  }
}
public class Slider {
  //Sliders
  PImage barra1;
  PImage indicatore1;
  PImage barra2;
  PImage indicatore2;
  float easing = 0.1f; 
  int tsize=24;
   int x1=50, y1=50, x2=180, y2=95,x3=50, y3=250, x4=180, y4=245;

  public Slider() {
  }

  public void sliderset() {
    barra1 = loadImage("barra1.png");
    indicatore1 = loadImage("indicatore1.png");
    barra2 = loadImage("barra2.png");
    indicatore2 = loadImage("indicatore2.png");
  }
  public void slider1() {

    textAlign(LEFT);
    textSize(tsize);
    fill(0);
    text("Servopinza", 50, 150);

    image(barra1, x1, y1+50);
    image(indicatore1, x2, y2);

    if (mousePressed && mouseY < y2+20) {
      float targetX1 = constrain(mouseX, 50, 350);
      float dx = targetX1 - x2;
      x2 += dx * easing;
      //arduino.servoWrite(5, constrain(mouseX / 2, 0, 180));
      target1=targetX1;
    }
  }
  public void slider2() {
    textAlign(LEFT);
    textSize(tsize);
    fill(0);
    image(barra2, x3, y3);
    image(indicatore2, x4, y4);
    text("Servomotor", 50, 300);
    if (mousePressed && mouseY > y4-20) {
      float targetX2 = constrain(mouseX, 50, 350);
      float dx = targetX2 - x4;
      x4 += dx * easing;
      //arduino.servoWrite(9, constrain(mouseX / 2, 0, 180));
      target2=targetX2;
    }
  }
}
public class Switchcommand {

int  graycol=130;
  public Switchcommand (){}
  
  public void setup(){
  //icon

  cp5.addIcon("icon", 10)
    .setPosition(450, 150)
    .setSize(70, 50)
    .setRoundedCorners(20)
    .setFont(createFont("fontawesome-webfont.ttf", 60))
    .setFontIcons(0xff00f205, 0xff00f204)
    //.setScale(0.9,1)
    .setSwitch(true)
    .setColorBackground(color(255, 100))
    .hideBackground()
    ;


  font12 = createFont("Arial", 12);
  font24 = createFont("Arial", 28);
  background(255); 
  fill(graycol); 
  stroke(33); 
  strokeWeight(0);  
  }
  

}
public class Termom {
  float y, h;
  
  public Termom() {
  }
  //Disegno termometro
  public void bulbo() {
    // Bulbo
    fill(200, 0, 0);
    smooth();
    stroke(0, 46, 200);
    strokeWeight(8);
    ellipse(250+1000, 250+300, 58, 50);
  }

  public void termometro() {
    //Termometro
    noStroke();
    fill(0, 46, 200);
    arc(250+1000, 30+300, 30, 20, PI, PI+PI);
    rect(235.2f+1000, 30+300, 30, 200);
  }

  public void mercurio() {
    // Disegno solco mercurio
    fill(250, 250, 250);
    rect(245+1000, 30+300, 10, 200);
    
      // Mercurio
  fill(200, 0, 0);
  smooth();
  strokeWeight(0);
  y= -2.0f*tempC + 170;
  h = 240-y;
  rect(245.2f+1000, y+300, 10, h);
  }
  public void num() {

    // Valori numerici termometro
    stroke(245, 240, 220);
    strokeWeight(1);
    textAlign(RIGHT);
    fill(0, 46, 250);

    // Centigrade
    textAlign(LEFT);
    for (int i = 0; i < 6; i += 1) {
      line(268+1000, 204-35*i+300, 278+1000, 204-35*i+300);
      if (i < 5) line(268+1000, 187-35*i+300, 273+1000, 187-35*i+300);
      textFont(font12);
      text(str(0+10*i), 282+1000, 210-35*i+300);
    }
  }
  public void disegna(){
    bulbo();
  termometro();
  mercurio();
  num();
  }
}
  public void settings() {  size(1400, 700); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--present", "--window-color=#666666", "--stop-color=#cccccc", "graphic" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
