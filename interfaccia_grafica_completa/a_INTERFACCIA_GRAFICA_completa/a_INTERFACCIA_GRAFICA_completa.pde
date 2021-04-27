import controlP5.*;
ControlP5 cp5;
import processing.serial.*;
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

Termom termom= new Termom(); 
Schermo schermo=new Schermo();
Slider slider=new Slider();
Serialcomunication serialcomunication=new Serialcomunication();
Switchcommand switchcommand = new Switchcommand();
Grafico grafico = new Grafico();

void setup()
{
  size(1400, 700);
  background(255);

  MyPort =  new Serial(this, "/dev/tty.HC-05-SerialPort", 9600);
  //MyPort.bufferUntil('\n');
  grafico.setdati();
  cp5 = new ControlP5(this);
  switchcommand.setup();
  schermo.cuore(); // inizializza l'immagine del cuore 
  slider.sliderset();
}

void draw()
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
