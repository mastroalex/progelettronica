public class Slider {
  //Sliders
  PImage barra1;
  PImage indicatore1;
  PImage barra2;
  PImage indicatore2;
  float easing = 0.1; 
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
