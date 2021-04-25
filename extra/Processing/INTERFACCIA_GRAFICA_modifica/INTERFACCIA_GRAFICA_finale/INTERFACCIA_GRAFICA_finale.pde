import controlP5.*;
ControlP5 cp5;
import processing.serial.*;

Serial MyPort;

int x1=50, y1=50, x2=50, y2=95, x3=50, y3=250, x4=50, y4=245, Dx=50, Dy=50, R=10;

float target1;
float target2;
float easing = 0.1; 

long ti=0; 
long ti2=0; 

int end = 10;
float[] data; 
float[] datax; 
String dati = " ";
String valore="";
char dativec; 
int index = 0;
String newdati = " ";

boolean pulsante=false;


float tempC = 0;
float Incl = 0;
float Batt=0;
float y, h;

PFont font12;
PFont font24;

//Battito
PImage battitook;

int  graycol=130, tsize=24, xshift=4, yshift=50;

//Sliders
PImage barra1;
PImage indicatore1;
PImage barra2;
PImage indicatore2;




void setup()
{
  size(1400, 700);
  background(255);
  MyPort =  new Serial(this, "COM8", 9600);
  data = new float[1000];
  for (int i=0; i < data.length; i++) {
    data[i] = 100;
  }
  datax = new float[data.length];
  for (int i=0; i < datax.length; i++) {
    float passo=900/float(data.length);
    datax[i] = 50+i*passo;
  }


  //icon
  cp5 = new ControlP5(this);
  cp5.addIcon("icon", 10)
    .setPosition(450, 150)
    .setSize(70, 50)
    .setRoundedCorners(20)
    .setFont(createFont("fontawesome-webfont.ttf", 60))
    .setFontIcons(#00f205, #00f204)
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

  //battito
  battitook = loadImage("battitook.png");

  // slider
  barra1 = loadImage("barra1.png");
  indicatore1 = loadImage("indicatore1.png");
  barra2 = loadImage("barra2.png");
  indicatore2 = loadImage("indicatore2.png");
}

void draw()
{
  background(255);
  serialreceive();

  for (int i=0; i<data.length-1; i++) {
    fill(55, 200, 50);
    line(datax[i], 650-data[i], datax[i+1], 650-data[i+1]);
  }

  // Grafico
  stroke(0, 0, 0);
  line(50, 350, 50, 650);
  line(50, 650, 950, 650);
  fill(0, 0, 0);
  triangle(48, 350, 52, 350, 50, 340);
  triangle(940, 648, 940, 652, 950, 650);
  textSize(12);
  text("t(s)", 965, 665);
  text("V(v)", 15, 350);

  // Bulbo termometro
  fill(200, 0, 0);
  smooth();
  stroke(0, 46, 200);
  strokeWeight(8);
  ellipse(250+1000, 250+300, 58, 50);

  //Termometro
  noStroke();
  fill(0, 46, 200);
  arc(250+1000, 30+300, 30, 20, PI, PI+PI);
  rect(235.2+1000, 30+300, 30, 200);

  // Disegno solco mercurio
  fill(250, 250, 250);
  rect(245+1000, 30+300, 10, 200);
  
  // Mercurio
  fill(200, 0, 0);
  smooth();
  strokeWeight(0);
  y= -2.0*tempC + 170;
  h = 240-y;
  rect(245.2+1000, y+300, 10, h);

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
  
   // Sliders
  textSize(tsize);
  fill(0);
  text("Servopinza", 50, 150);
  text("Servomotor", 50, 300);
  image(barra1, x1, y1+50);
  image(indicatore1, x2, y2);
  image(barra2, x3, y3);
  image(indicatore2, x4, y4);

    if (mousePressed && mouseY < y2+20) {
      float targetX1 = constrain(mouseX, 50, 350);
      float dx = targetX1 - x2;
      x2 += dx * easing;
      target1=targetX1;
    }
    if (mousePressed && mouseY > y4-20) {
      float targetX2 = constrain(mouseX, 50, 350);
      float dx = targetX2 - x4;
      x4 += dx * easing;
      target2=targetX2;
    }

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

  //Rettangolo inclinazione
  fill(190);
  stroke(0);
  strokeWeight(1);
  rect(700, 70, 180, 140, 7);
  fill(0, 0, 0);
  textFont(font24);
  text("Roll", 760, 40);
  text(" °", 805, 150);
  text(nfc(Incl, 1), 750, 150);

  //Battito
  textFont(font24); 
  fill(250, 0, 0); 
  text("BPM", x1+xshift+950, y1-10); 
  fill(0, 0, 0);
  image(battitook, x1+900, y1+20);
  text(nfc(Batt, 0), 1017, 150);

  serialsend();
}


//icon
void icon(boolean theValue) {

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
    newdati = MyPort.readStringUntil('\n');
    //println(newdati);
    if ( newdati != null) {
      dati = newdati;
    }
    dati=dati.trim();
  }

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
      valore="1024";
    }
    if (index<data.length) {
      //data[index]=float(valore);
      data[index]=map(float(valore), 0, 1024, 0, 300);
      index++;
    } else if (index==data.length) {
      index=0;
      data[index]=map(float(valore), 0, 1024, 0, 300);
    }
    //   println(valore);
    // println(datax);
  }
}
