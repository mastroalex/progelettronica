import processing.serial.*;
import cc.arduino.*;
Arduino arduino;
Serial serial;

PImage immagine1;
PImage immagine2;
PImage immagine3;
PImage immagine4;

int tsize = 12;
int x1 = 100;
int y1 = 200;
int x2 = 100;
int y2 = 195;
int y3 = 350;
int x4 = 100;
int y4 = 345;
float easing = 0.1;

void setup() {
  arduino = new Arduino(this, "COM3", 9600);
  arduino.pinMode(5, Arduino.SERVO);
  arduino.pinMode(9, Arduino.SERVO);
  smooth();
  size(500,500);
  fill(0);
  noStroke();
  immagine1 = loadImage("Immagine1.png");
  immagine2 = loadImage("Immagine2.png");
  immagine3 = loadImage("Immagine3.png");
  immagine4 = loadImage("Immagine4.png");
    
  
}
void draw() {
  background(255);
  textSize(tsize);
  fill(0);
  text("Servopinza", 100, 242);
  text("Servomotor", 100, 392);
  image(immagine1, x1, y1);
  image(immagine2, x2, y2);
  image(immagine3, x1, y3);
  image(immagine4, x4, y4);
  if (mouseY < y1+20) {
      float targetX1 = constrain(mouseX, 100, 380);
      float dx = targetX1 - x2;
      x2 += dx * easing;
      arduino.servoWrite(5, constrain(mouseX / 2, 0, 180));
  }
  if (mouseY > y4-10) {
      float targetX2 = constrain(mouseX, 100, 380);
      float dx = targetX2 - x4;
      x4 += dx * easing;
      arduino.servoWrite(9, constrain(mouseX / 2, 0, 180));
  }
}
