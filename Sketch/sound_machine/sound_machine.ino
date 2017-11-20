#include <Adafruit_NeoPixel.h>

#define NUMBER_PIXEL 8
#define LEDPIN    6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, LEDPIN, NEO_GRB + NEO_KHZ800);

#include <Stepper.h>

int color [8][3] = {
  255,56,152,
  255,0,0,
  255,127,0,
  255,255,0,
  0,255,0,
  0,0,255,
  75,0,130,
  148,0,211
};

int num = 129;


int melody[129][2] = {

  1,600,
  1,600,
  1,600,
  1,600,
  2,600,
  2,600,
  3,300,
  4,600,
  3,300, 
  
  1,600,
  1,600,
  1,600,
  1,600,
  2,600,
  2,600,
  3,300,
  4,600,
  5,300,

  1,600,
  1,600,
  1,600,
  1,600,
  2,600,
  2,600,
  3,300,
  4,600,
  3,300,

  1,600,
  1,600,
  1,600,
  1,600,
  2,600,
  2,600,
  3,300,
  4,600,
  5,300,

  0,300,
  0,300,
  0,300,
  0,300,
  3,300,
  4,600,
  3,300,

  0,300,
  0,300,
  0,300,
  0,300,
  3,300,
  4,600,
  5,300,

  0,300,
  0,300,
  0,300,
  0,300,
  3,300,
  4,600,
  3,300,

  0,300,
  0,300,
  0,300,
  0,300,
  3,300,
  4,600,
  5,300,

  5,300,
  6,300,
  0,300,
  5,300,
  3,300,
  4,600,
  3,300,

  5,300,
  6,300,
  0,300,
  5,300,
  3,300,
  4,600,
  5,300,

  5,300,
  6,300,
  0,300,
  5,300,
  3,300,
  4,600,
  3,300,

  5,300,
  6,300,
  0,300,
  5,300,
  3,300,
  4,600,
  5,300,

  5,600,
  5,600,
  5,600,
  5,600,
  5,600,
  5,600,
  3,300,
  4,600,
  5,300, 

  5,600,
  5,600,
  5,600,
  5,600,
  5,600,
  5,600,
  3,300,
  4,600,
  1,300,

  5,600,
  5,600,
  5,600,
  5,600,
  5,600,
  5,600,
  3,300,
  4,600,
  5,300,

  5,600,
  5,600,
  5,600,
  5,600,
  5,600,
  5,600,
  3,300,
  4,600,
  1,300,

  5,1000
  
};

float wait;

int pos = 0;
int mode = 1;

int in1Pin = 11;
int in2Pin = 10;
int in3Pin = 9;
int in4Pin = 8;
 
// change this to the number of steps on your motor
#define STEPS 200
 
Stepper motor(STEPS, in1Pin, in2Pin, in3Pin, in4Pin); 
 
void setup()
{
  strip.begin();//initialises neopixels
  strip.setBrightness(255);// set brightness from 0 to max is 255
  strip.show();//clears any previous data in the strip

  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
 
  motor.setSpeed(100);
  
  int note = 0;
  int direct;
  int dist;
    for (int i=0;i<num;i++){
      
      if (i==36) mode = 2;
      if (i==92) mode = 1;
      if (i==98) mode = 2;
      if (i==101) mode = 1;
      if (i==107) mode = 2;
      if (i==110) mode = 1;
      if (i==116) mode = 2;
      if (i==119) mode = 1;
      if (i==125) mode = 2;
      
 
      note = melody[i][0]; 
      dist =  note - pos; 
      direct = 1;

      if (dist < 0) {
        dist = abs(dist); 
        direct = -1;
      }
    
   
    motor.step(dist*10*direct);
    Serial.println(note);
  
    
    if(mode == 1){
    int ran = floor(random(8));
    strip.setPixelColor(24+note*2, color[ran][0], color[ran][1], color[ran][2]);
    strip.show(); 
    if(i<num-1) wait = melody[i][1]- abs(melody[i+1][0] - note)*28;
    delay(wait-100); 
    strip.clear();
    strip.show();
    delay(100);
    }

    else if (mode == 2){  
    int ran = floor(random(8));
    strip.setPixelColor(24+note*2, color[ran][0], color[ran][1], color[ran][2]);
    strip.show();
    if(i<num-1) wait = melody[i][1]- abs(melody[i+1][0] - note)*28;
    int temp1 = note; int temp2 = note;
    int max1 = 7 - note;
    if (max1<4) max1 = 7 - max1;  
    for(int i=1;i<=max1;i++){
      temp1 +=1; temp2 -=1; 
      if(temp1<=7) strip.setPixelColor(24+temp1*2, color[ran][0], color[ran][1], color[ran][2]);
      if(temp2>=0) strip.setPixelColor(24+temp2*2, color[ran][0], color[ran][1], color[ran][2]);
      strip.show();
      delay(wait/max1);
      }
    strip.clear();   
    strip.show();
    }

    else if (mode == 3){  
    strip.setPixelColor(24+note*2, 255, 0, 0);
    strip.show();
    if(i<num-1) wait = melody[i][1]- abs(melody[i+1][0] - note)*28;
    int temp1 = note; int temp2 = note;
    int max1 = 7 - note;
    if (max1<4) max1 = 7 - max1;  
    for(int i=1;i<=max1;i++){
      temp1 +=1; temp2 -=1; 
      if(temp1<=7) strip.setPixelColor(24+temp1*2, 255, 0, 0);
      if(temp2>=0) strip.setPixelColor(24+temp2*2, 255, 0, 0);
      strip.show();
      delay(wait/max1);
      }
    strip.clear();   
    strip.show();
    }
    
    

    
    
    pos = note;
    
    }
      
    
   
    
  
}

void loop(){
}





