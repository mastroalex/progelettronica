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
    .setFontIcons(#00f205, #00f204)
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
