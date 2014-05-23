#include <math.h>

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define SDPOWER            -1

#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define PS_ON_PIN          12
#define KILL_PIN           -1

int counter;
int xDIR, yDIR;
int R=10, newx, newy, oldx, oldy,xmove,ymove,xsign,ysign;

void setup() {
  pinMode(LED_PIN  , OUTPUT);
  
  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);
  pinMode(X_ENABLE_PIN    , OUTPUT);
  
  pinMode(Y_STEP_PIN  , OUTPUT);
  pinMode(Y_DIR_PIN    , OUTPUT);
  pinMode(Y_ENABLE_PIN    , OUTPUT);
    
  digitalWrite(X_ENABLE_PIN    , LOW);
  digitalWrite(Y_ENABLE_PIN    , LOW);
  Serial.begin(115200);
    
  counter=0;
  xDIR=0;
  yDIR=0;
}

unsigned long prevMillis;

void goX(){
  if(xDIR!=1){
    digitalWrite(X_DIR_PIN    , HIGH);
    xDIR=1;
  }
  digitalWrite(X_STEP_PIN    , HIGH);
  delay(1);
  digitalWrite(X_STEP_PIN    , LOW);
}

void goY(){
  if(yDIR!=1){
    digitalWrite(Y_DIR_PIN    , HIGH);
    yDIR=1; 
  }
  digitalWrite(Y_STEP_PIN    , HIGH);
  delay(1);
  digitalWrite(Y_STEP_PIN    , LOW);
}

void goXneg(){
  if(xDIR!=-1){
    digitalWrite(X_DIR_PIN    , LOW);
    xDIR=-1;
  }
  digitalWrite(X_STEP_PIN    , HIGH);
  delay(1);
  digitalWrite(X_STEP_PIN    , LOW);
}

void goYneg(){
  if(yDIR!=-1){
    digitalWrite(Y_DIR_PIN    , LOW);
    yDIR=-1;
  }
  digitalWrite(Y_STEP_PIN    , HIGH);
  delay(1);
  digitalWrite(Y_STEP_PIN    , LOW);
}

float deg2rad(int deg){
  float radval=deg*3.14159/180;
  return radval;
}

void loop () {
  
  counter = counter+1;
  
  //calculate dx and dy
  newx=R*sin(deg2rad(counter%360));
  newy=R*cos(deg2rad(counter%360));
  
  xmove=ceil(oldx-newx);
  ymove=ceil(oldy-newy);

  xsign=xmove/(abs(xmove)+0.0001);
  ysign=ymove/(abs(ymove)+0.0001);
  
  //move x axis
  if(xsign==1){
    for (int i = 1; i < xmove; i++) { 
      goX();
    }
  }
  if(xsign==-1){
    for (int i = 1; i < -xmove; i++) { 
      goXneg();
    }
  }
  if(xsign==0){
    //no move
  }
  
  //move y axis
  if(ysign==1){
    for (int i = 1; i < ymove; i++) { 
      goY();
    }
  }
  if(ysign==-1){
    for (int i = 1; i < -ymove; i++) { 
      goYneg();
    }
  }
  if(ysign==0){
    //no move
  }
  
    
  oldx=newx;  
  oldy=newy;
}

