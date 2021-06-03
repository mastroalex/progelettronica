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
