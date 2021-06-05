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
    rect(235.2+1000, 30+300, 30, 200);
  }

  public void mercurio() {
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
