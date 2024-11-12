#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define minPos 45
#define servo 9
#define led 7
#define maxPos 110

#define busy 4
#define pir 11
#define tx 2
#define rx 3
unsigned long int d,//grado corrente del motore
                  t=0,//istante di tempo
                  dt;//differenza di tempo
int dStep=1,
    currentPirState,//stato attuale del PIR
    lastPirState;//ultimo stato del PIR
bool movement=false,//vera se il pir irleva qualcosa
     playerBusy=true;//falsa se il player sta suonando qualcosa
Servo servoMotor;
SoftwareSerial swSerial(rx,tx);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  Serial.println("inizio");
  pinMode(servo,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(pir,INPUT);
  pinMode(busy,INPUT);
  servoMotor.attach(servo);
  
  swSerial.begin(9600);
  Serial.println("connessione a df player mini");
  if(!player.begin(swSerial)){
    Serial.println("connessione fallita");
    while(true);
  }
  Serial.println("connessione stabilita");
  player.volume(30);
  
}

void loop() {
  
  
  currentPirState=digitalRead(pir);
  playerBusy=digitalRead(busy);
  if(currentPirState==HIGH && lastPirState==LOW){//pir ha rilevato movimento
    digitalWrite(led,currentPirState);
    movement=true;
    Serial.println("pir on");
    if(playerBusy){
      player.play(1);
      Serial.println("suono");
    }
  }
  if(currentPirState==LOW && lastPirState==HIGH){//pir smette di rilevare
    digitalWrite(led,currentPirState);
    movement=false;
    Serial.println("pir off");
  }
  
  dt=millis()-t;//movimento del servo motore
  if(dt>=15 && !playerBusy){
   t=millis();
    d+=dStep;
    if(d>=maxPos){
      d=maxPos;
      dStep=-1;
      delay(700);
    }
    else if(d<=minPos ){
      d=minPos;
      dStep=1;
      delay(100);
    }
    servoMotor.write(d);
  }
  lastPirState=currentPirState;

}
