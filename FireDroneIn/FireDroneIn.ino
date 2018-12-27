#include <Servo.h>

int Endstop = A1;

int EndstopSig=800;


int XTangle = 130;
int YTangle = 155;


int DeXTangle = 20;
int DeYTangle = 180;
int serT = 10;



Servo sX;
Servo sY;

int fireDel = 5000;


void TargetAngle(int Xangle, int Yangle){
  sX.attach(5);
  sY.attach(6);
  while(1){
    if(sX.read()<Xangle)sX.write(sX.read()+1);
    if(sX.read()>Xangle)sX.write(sX.read()-1);
    if(sY.read()<Yangle)sY.write(sY.read()+1);
    if(sY.read()>Yangle)sY.write(sY.read()-1);
    if (sX.read()==Xangle && sY.read()==Yangle)break;
    delay(serT);
  }
  delay(fireDel);
//  sX.write(Xangle);
//  sY.write(Yangle);
}

void DeTargetAngle(int Xangle, int Yangle){

  while(1){
    if(sX.read()<Xangle)sX.write(sX.read()+1);
    if(sX.read()>Xangle)sX.write(sX.read()-1);
    if(sY.read()<Yangle)sY.write(sY.read()+1);
    if(sY.read()>Yangle)sY.write(sY.read()-1);
    if (sX.read()==Xangle && sY.read()==Yangle)break;
    delay(serT);
  }
  delay(1000);
    sX.detach();
  sY.detach();
}

void setup() {
  sX.attach(5);
  sY.attach(6);
  DeTargetAngle(DeXTangle,DeYTangle);
  Serial.begin(9600);
}

void loop() {
if(analogRead(Endstop)>EndstopSig){
  TargetAngle(XTangle,YTangle);
  }
  else{
    DeTargetAngle(DeXTangle,DeYTangle);
  }
Serial.println(analogRead(A1));
//TargetAngle(XTangle,YTangle);
//DeTargetAngle(DeXTangle,DeYTangle);
}
