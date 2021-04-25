public class Grafico {
 public float[] data; 
public float[] datax; 
 public Grafico(){}
 
 public void setdati(){
 data = new float[1000];
  for (int i=0; i < data.length; i++) {
    data[i] = 100;
  }
  datax = new float[data.length];
  for (int i=0; i < datax.length; i++) {
    float passo=900/float(data.length);
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
