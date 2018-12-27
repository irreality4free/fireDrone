//Pins
int ena = 9;
int dir = 8;
int pulse = 7;
int Home = 12;
int EndStop = A1;
int Pump = 10;
int Button = 6;


//Signals
int HomeDir = 0;
int EndstopSig = 0;
int pumpSig = 1;

//Const
long offset = 1500;
long stepsHome = 170000- offset;
int RegSpeed = 20;
long fireTime = 60000;
int timeToTarget = 2000;




//Funcs
void MakeStep(int Speed) {
  digitalWrite(pulse, LOW);
  delayMicroseconds(Speed);
  digitalWrite(pulse, HIGH);
  delayMicroseconds(Speed);
}

void GoSteps(long steps, int Dir, int Speed) {
  digitalWrite(dir, Dir);
  for (long i = 0; i < steps; i++) {
    MakeStep(Speed);
  }
  
}

void GoHydro(int Speed) {
  GoSteps(stepsHome, HomeDir, Speed);
}

void GoEndPoint(int Speed) {
  digitalWrite(ena, HIGH);
  digitalWrite(dir, !HomeDir);
  while (digitalRead(EndStop) == EndstopSig) {
    MakeStep(Speed);
  }
  GoSteps(offset, HomeDir, Speed);
  Serial.println("out of endpoint");
  digitalWrite(ena, LOW);
}

void Calibrate() {
  digitalWrite(ena, HIGH);
  GoEndPoint(RegSpeed);
//  GoHome(RegSpeed);
digitalWrite(ena, LOW);
}

void pumpIt(long del) {
  digitalWrite(Pump, pumpSig);
  delay(del);
  digitalWrite(Pump, !pumpSig);
}

void Fire() {
  digitalWrite(ena, HIGH);
  GoHydro(RegSpeed);
  delay(timeToTarget);
  pumpIt(fireTime);
     delay(10000);
  GoEndPoint(RegSpeed);
  digitalWrite(ena, LOW);
}





//MAIN

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
  pinMode(EndStop, INPUT_PULLUP);
  pinMode(Pump, OUTPUT);
  digitalWrite(ena, LOW);
  digitalWrite(dir, HIGH);
//  Calibrate();
  Serial.begin(9600);
//  delay(5000);
//  GoSteps(100000,0,RegSpeed);
//  for (long i = 0; i < 100000; i++) {
//    MakeStep(RegSpeed);
//  }
GoEndPoint(RegSpeed);
//GoHydro(RegSpeed);
//Fire();
}



void loop() {
  if (!digitalRead(Button)) {
    GoEndPoint(RegSpeed);
    Serial.println("fire");
    Fire();
 
  }
//GoEndPoint(RegSpeed);
//Serial.println(digitalRead(A0));
//Calibrate();
//GoHome(RegSpeed);
//GoSteps(5000,0,50);
//  digitalWrite(Pump, HIGH);
//  delay(3000);
//  digitalWrite(Pump, LOW);
//  delay(3000);
Serial.println(digitalRead(A1));
}
