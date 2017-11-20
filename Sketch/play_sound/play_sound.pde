import ddf.minim.*;
import ddf.minim.analysis.*;

import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
int no;
float dist = -1;
float pdist;
boolean released = true;
int count = 0;
int aa,bb;


Minim m;
AudioSample[] note = new AudioSample[13];


void setup(){
  size(512, 200);
  frameRate(90);
  m = new Minim(this);
  for(int i=0; i<10; i++){
    note[i] = m.loadSample(str(i)+".wav",128);
  }
  
  
  String portName = Serial.list()[3]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw(){
  
 
}

void serialEvent(Serial myPort) {
  bb = millis()- aa; aa = millis();  println(bb);
  val = myPort.readStringUntil('\n');       

    
    if(val != null){
      
   
      no = int( float(val) ); println(no);
      note[no].trigger(); //bb = frameCount- aa; aa = frameCount;  println(bb); 
      
   
    }
}