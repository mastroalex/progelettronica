import controlP5.*;
ControlP5 cp5;
import processing.serial.*;

//Grafico
Serial MyPort;
String dati = "";

int end = 10;
float [] values= new float [1000]; 


float X0 = 0.0;
float Y0 = 0.0;
float X1 = 0.0;
float Y1 = 0.0;

//Termometro
float tempC = 0;
float Incl = 0;
float Batt=0;
float y, h, msbyte, lsbyte;
int yDist, xx=-15;

PFont font12;
PFont font24;

//Battito
PImage battitook;
float easing = 0.1; 
int  graycol=130, tsize=24, xshift=4, yshift=50;
int x1=50, y1=50, x2=50, y2=95, x3=50, y3=250, x4=50, y4=245, Dx=50, Dy=50, R=10;


//Sliders
PImage barra1;
PImage indicatore1;
PImage barra2;
PImage indicatore2;




void setup()
{
  //Grafico
  background(255);
  for (int i=0; i<= values.length; i++){
    values [i] = 0;
  }
  
  
  //icon
  size(1400,700);
  cp5 = new ControlP5(this);
  cp5.addIcon("icon",10)
     .setPosition(450,150)
     .setSize(70,50)
     .setRoundedCorners(20)
     .setFont(createFont("fontawesome-webfont.ttf", 60))
     .setFontIcons(#00f205,#00f204)
     //.setScale(0.9,1)
     .setSwitch(true)
     .setColorBackground(color(255,100))
     .hideBackground()
     ;
      
     
font12 = createFont("Arial", 12);
font24 = createFont("Arial",28);
size(1400,700); background(255); 
fill(graycol); stroke(33); strokeWeight(0);  
 
 battitook = loadImage("battitook.png");
 
 barra1 = loadImage("barra1.png");
  indicatore1 = loadImage("indicatore1.png");
  barra2 = loadImage("barra2.png");
  indicatore2 = loadImage("indicatore2.png");

size(1400, 700);



 }
 
void draw()
{
  //Grafico
  background(255);
  
  stroke(0,0,250);
  strokeWeight(2);
  //line(50,800-V,950,800-V);
  stroke(0,0,0);
  line(50,350,50,650);
  line(50,650,950,650);
  fill(0,0,0);
  triangle(48,350,52,350,50,340);
  triangle(940,648,940,652,950,650);
  textSize(12);
  text("t(s)",965,665);
  text("V(v)",15,350);
  
  //grafico
  // while(MyPort.available()>0)
  
    
    //dati = MyPort.readStringUntil(end);
    if(dati != "")
  {
    
    String[] v = split(dati,',');
    Y0 = float(v[0]);
    Y1 = float(v[1]);
    X0 = float(v[2]);
    X1 = float(v[3]);
    dati ="";
    
  }
  
  
  
  
  stroke(255,0,0);
  line(X0,490-Y0,X1,490-Y1);

  if(Y1 > 296)
  {
    noLoop();
  }
  //delay(200);
  

 
 
 
//Disegno termometro
// Bulbo
fill(200, 0, 0);
smooth();
stroke(0, 46, 200);
strokeWeight(8);
ellipse(250+1000, 250+300, 58, 50);

//Termometro
noStroke();
fill(0, 46, 200);
arc(250+1000, 30+300, 30, 20, PI, PI+PI);
rect(235.2+1000,30+300,30,200);

// Disegno solco mercurio
fill(250, 250, 250);
rect(245+1000,30+300,10,200);

// Valori numerici termometro
stroke(245, 240, 220);
strokeWeight(1);
textAlign(RIGHT);
fill(0,46,250);



// Centigrade
textAlign(LEFT);
for (int i = 0; i < 6; i += 1) {
line(268+1000, 204-35*i+300, 278+1000, 204-35*i+300);
if(i < 5) line(268+1000, 187-35*i+300, 273+1000, 187-35*i+300);
textFont(font12);
text(str(0+10*i), 282+1000, 210-35*i+300);

//Sliders
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
      //arduino.servoWrite(5, constrain(mouseX / 2, 0, 180));
  }
  if (mousePressed && mouseY > y4-20) {
      float targetX2 = constrain(mouseX, 50, 350);
      float dx = targetX2 - x4;
      x4 += dx * easing;
      //arduino.servoWrite(9, constrain(mouseX / 2, 0, 180));
  }

}

// Mercurio
fill(200,0, 0);
smooth();
strokeWeight(0);
y= -2.0*tempC + 268;
h = 240-y;
rect(245.2+1000, y+300, 10, h);

// Rettangolo dati 
fill(190);
stroke(0);
strokeWeight(1);
rect(1200,70,180,140,7);
fill(0,0,0);
textFont(font24);
textAlign(LEFT);
text("Temperature", 1210,40);
text("°C", 1300, 150);
text(nfc(tempC, 1), 1250, 150);

//Rettangolo inclinazione
fill(190);
stroke(0);
strokeWeight(1);
rect(700,70,180,140,7);
fill(0,0,0);
textFont(font24);
text("Roll",760,40);
text("°C",800,150);
text(nfc(Incl,1),750,150);



//Battito
textFont(font24); fill(250,0,0); text("BPM",x1+xshift+950,y1-10); 
fill(0,0,0);
image(battitook,x1+900,y1+20);
text(nfc(Batt,0),1030,150);



}
//icon
void icon(boolean theValue) {
  println("got an event for icon", theValue);
} 




 
