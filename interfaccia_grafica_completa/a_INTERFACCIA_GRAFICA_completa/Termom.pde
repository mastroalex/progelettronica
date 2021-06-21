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
    ellipse(1250, 550, 58, 50);
  }

  public void termometro() {
    //Termometro
    noStroke();
    fill(0, 46, 200);
    arc(1250, 330, 30, 20, PI, PI+PI);
    rect(1235.2, 330, 30, 200);
  }

  public void mercurio() {
    // Disegno solco mercurio
    fill(250, 250, 250);
    rect(1245, 330, 10, 200);
    
      // Mercurio
  fill(200, 0, 0);
  smooth();
  strokeWeight(0);
  float y = map(tempC, 0, 50, 0, 175);  //175 è l'altezza tra la tacca 0 e 50
  h = -y-66; // valore tra il bublo e la tacca 0
  rect(1245.2, 570, 10, h);
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
      line(1268, 504-35*i, 1278, 504-35*i);
      if (i < 5) line(1268, 487-35*i, 1273, 487-35*i);
      textFont(font12);
      text(str(0+10*i), 1282, 510-35*i);
    }
  }
  public void disegna(){
    bulbo();
  termometro();
  mercurio();
  num();
  }
}
