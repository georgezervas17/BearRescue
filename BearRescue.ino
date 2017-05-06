#include <Servo.h>

Servo myservo;
int frontSensorCounter;
int backSensorCounter;
int leftSensorCounter;
int USFrontEchoPin = 12;//mprosta
int USFrontTrigPin = 13;

int echoPin = 8; //mprosta aristera
int trigPin = 9;

int echoPin2 = 2;//pisw aristera
int trigPin2 = 4;

int echoPin3 = 15;//pisw
int trigPin3 = 14;

int echoPin4 = 17;//pisw deksia
int trigPin4 = 16;

int echoPin5 = 19;//mprosta deksia
int trigPin5 = 18;

//Left
int MotorLeftA = 5;
int MotorLeftB = 6;
//Right
int MotorRightA = 11;
int MotorRightB = 10;
boolean movementdone=false;
int frontcounter=0;
boolean found=false;
boolean checkleft=false;
boolean checkright=false;
int gripper = 20; //dagkkana
int padding=25;
int backcounter=0;

int trig1=31;
int trig2=43;

void setup() {

  Serial.begin(19200);
  myservo.attach(3);
  frontSensorCounter=0;
  backSensorCounter=0;
  leftSensorCounter=0;
  pinMode(MotorLeftA, OUTPUT);
  pinMode(MotorLeftB, OUTPUT);
  pinMode(MotorRightA, OUTPUT);
  pinMode(MotorRightB, OUTPUT);

  pinMode(trig1, INPUT);
  pinMode(trig2, INPUT);
  
  pinMode(USFrontTrigPin, OUTPUT); //MPROSTA
  pinMode(USFrontEchoPin, INPUT);
  
  pinMode(trigPin, OUTPUT); //MPROSTA ARISTERA
  pinMode(echoPin, INPUT);
  
  pinMode(trigPin2, OUTPUT); //PISW ARISTERA
  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);//PISW
  pinMode(echoPin3, INPUT);
  
  pinMode(trigPin4, OUTPUT);//PISW DEKSIA
  pinMode(echoPin4, INPUT);
  
  pinMode(trigPin5, OUTPUT);//MPROSTA DEKSIA
  pinMode(echoPin5, INPUT);
}

void loop()
{
 //Serial.println(readbackright());

  long duration, cm, duration2, cm2, duration3, cm3,duration4, cm4,duration5, cm5,duration6, cm6;
  //Serial.println(readback());

if(digitalRead(trig1)==0){
    myservo.write(130);


  do{
    checkParalelAcc( readfrontleft(),readbackleft(),true);
    if ( readfront() < 23 )
    {
      frontcounter++;
      do {   
        turnRight();
        delay(5);
      } while ( readfrontleft() != readbackleft() || readbackleft() - readfrontleft() > 1);
    checkParalelAcc( readfrontleft(),readbackleft(),true);
    }
  
    else if ( readfrontleft() > 40 && readbackleft() < 20 && frontcounter>5)
    {
      movementdone=true;
      goForward();
      delay(600); 
      checkParalelAcc(readbackright(),readfrontright(),false);
      break;
    }
    
    checkParalelAcc( readfrontleft(),readbackleft(),true);
    
  }while(!movementdone);

  movementdone=false;
  
  //GIA TIS ARISTERES STROFES
  do{
    checkParalelAcc(readbackright(),readfrontright(),false);
    if ( readfront() < 25 )
    {
      do {
        turnLeft();
        delay(5);
      } while ( readfrontright() != readbackright() || readbackright() - readfrontright() > 1);   
    }
    if(readfront()>90){
      frontSensorCounter++;
    }
    else{
      frontSensorCounter=0;
    }

    if(readback()>140){
      backSensorCounter++;
    }
    else{
      backSensorCounter=0;
    }

    if(readbackleft()>100){
      leftSensorCounter++;
    }
    else{
      leftSensorCounter=0;
    }
    checkParalelAcc(readbackright(),readfrontright(),false);

    
    if(frontSensorCounter>5 &&backSensorCounter>5 &&leftSensorCounter>5){
      
    }
  
    
    
    else if(frontSensorCounter>5 && backSensorCounter>5){
                
       stopMoving();
       myservo.write(140);
       delay(1000);
        
      do{
        
        turnLeftSearch();
        delay(50);
        stopMoving();
        delay(10);
        
        if(digitalRead(trig1)==1){
              do{
                goForwardBear();
                
              }while(!digitalRead(trig1)==0);
          }      
         

         if(digitalRead(trig2)==0){
           turnLeft();
           delay(50);
           goForward();
           delay(500);
           myservo.write(3);
           stopMoving();
           delay(500);
           found=true;      
                  
          }
          
          
     }while(!found);       


         //AFOU TO VREI TO ARKOUDI PAEI NA VREI TOIXO
         if(found){
            do{
              goBackward1();
            }while(readback()>36);

            do{   
            turnRight1();
            delay(50);
            goBackward();
            delay(10);

            if(readfrontright()<15){
                do{   
                   turnRight();
                   delay(10);   
                 }while ( readfrontright() != readbackright() || readbackright() - readfrontright() > 3);  
                  break;
              }
          }while ( readfrontright() != readbackright() || readbackright() - readfrontright() > 1);   

         movementdone=true;
         }
    }//end else if
  }while(!movementdone);

     frontSensorCounter=0;
  movementdone=false;
  

  //GIA NA EPISTREPSEI ME VASH TON TOIXO STA ARISTERA TOU OPWS GURNAEI
  do{
    
     bcheckParalelAcc( readbackright(),readfrontright(),false);
    //AN VREI MPROSTA TOIXO STRIPSE DEKSIA
    if(readback()<32){
        do{   
            turnRight1();
            delay(50);
            goBackward();
            delay(5);

          }while ( readfrontright() != readbackright() || readbackright() - readfrontright() > 3);  
              
     bcheckParalelAcc(readbackright(),readfrontright(),false); 
    }
    
    else if ( readbackright()>40 && readback()<60 ){
      bcheckParalelAcc( readbackright(),readfrontright(),false);
      movementdone=true;
      
      goBackward();
      delay(1000);
      break;
    }
    
    bcheckParalelAcc( readbackright(),readfrontright(),false);
  }while(!movementdone);
  
  movementdone=false;


  //UPOLOIPH KINHSH GIA MEXRI AFETHRIA
  do{
    bcheckParalelAcc(readbackleft(),readfrontleft(),true);
    if (readfrontleft() < 25 && readfrontright() < 20 && readback() < 20)
    {
      movementdone=true;
      goBackward();
      delay(1000);
      stopMoving();
      delay(2000);
    }
    else if(readback()<28){
        do{   
          turnLeft1();
          delay(50);
          goBackward();
          delay(10);
            if( readbackleft()<15&& readbackright()<15 && readback()<50){
              do{
                  bcheckParalelAcc(readbackright(),readfrontright(),false);
                }while(readback()>10);
              stopMoving();
              delay(10000);
              movementdone=true;
            }
        }while ( readfrontleft() != readbackleft() || readfrontleft() - readbackleft() > 3);   
    }//end else if
    bcheckParalelAcc(readbackleft(),readfrontleft(),true);
    
  }while(!movementdone);
  
  movementdone=false;


 }
  else{
    stopMoving();
  }
}
  
  
void bcheckParalelAcc(long cm1, long cm2, boolean mode) {
  //GIA TOIXO STOUS ARISTEROUS KATA THN FORA TOU ROBOT PROS TA MPROSTA.
  if (cm1>14 && cm2>14 && mode){
    bturnRightP();
  }
  else if(cm1<12 && (cm2<12 || cm2>150) && mode){
    bturnLeftP();
  }

  //GIA TOIXO STOUS DEKSIOUS KATA THN FORA TOU ROBOT PROS TA MPROSTA.
  else if (cm1>18 && cm2>18 && !mode){
    bturnLeftP();
  }
  else if(cm1<16 && (cm2<16|| cm2>150) && !mode){
    bturnRightP();
  }

  else if(cm1<10 && cm2<10){
    bturnRightP();
    delay(50);
  }
  
  else if (cm1 - cm2 > 2 || mode) {
    bturnRightP();
    delay(10);
  }
  
  else if (cm2 - cm1 > 2) {
    bturnRightP();
    delay(5);
  }
  else goBackward();  
  
}
void checkParalelAcc(long cm1, long cm2, boolean mode) {
  if (cm1>13 && cm2>13 && mode){
    turnLeftP();
  }
  else if(cm1<11 && cm2<11 && mode){
    turnRightP();
  }
  else if (cm1>15 && cm2>15 && !mode){
    turnRightP();
  }
  else if(cm1<13 && cm2<13 && !mode){
    turnLeftP();
  }
  else if (cm1 - cm2 > 1) {
    turnLeftP();
    delay(10);
  }
  else if (cm2 - cm1 > 1) {
    turnRightP();
    delay(5);
  }
  else goForward();  
}


void checkParalelS(long cm1, long cm2, boolean mode) {
  if (cm1>7 && cm2>7 && mode){
    turnLeftP();
  }
  else if(cm1<5 && cm2<5 && mode){
    turnRightP();
  }

  else if (cm1>32 && cm2>32 && !mode){
    turnRightP();
  }
  else if(cm1<30 && cm2<30 && !mode){
    turnLeftP();
  }
  else if (cm1 - cm2 > 1) {
    turnLeftP();
    delay(10);
  }
  else if (cm2 - cm1 > 1) {
    turnRightP();
    delay(5);
  }
  else goForward();  
}

void stopMoving() {
  digitalWrite(MotorLeftA, LOW);
  analogWrite(MotorLeftB, LOW);
  digitalWrite(MotorRightA, LOW);
  digitalWrite(MotorRightB, LOW);
}
void goForward() {
  digitalWrite(MotorLeftA, LOW);
  analogWrite(MotorLeftB, 225);
  digitalWrite(MotorRightA, LOW);
  digitalWrite(MotorRightB, HIGH);
}

void goForwardBear() {
  digitalWrite(MotorLeftA, LOW);
  analogWrite(MotorLeftB, 125);
  digitalWrite(MotorRightA, LOW);
  analogWrite(MotorRightB, 155);
}

void turnRight() {
  digitalWrite(MotorLeftA, LOW);
  analogWrite(MotorLeftB, 80);
  analogWrite(MotorRightA, 80);
  digitalWrite(MotorRightB, LOW);
}

void turnLeft() {
  analogWrite(MotorLeftA, 120);
  digitalWrite(MotorLeftB, LOW);
  digitalWrite(MotorRightA, LOW);
  analogWrite(MotorRightB, 120);
}
void turnRight1() {
  analogWrite(MotorLeftA, 30);
  digitalWrite(MotorLeftB, LOW);
  analogWrite(MotorRightA, 255);
  digitalWrite(MotorRightB, LOW);
}
void turnLeft1() {
  analogWrite(MotorLeftA, 250);
  digitalWrite(MotorLeftB, LOW);
  analogWrite(MotorRightA, 30);
  digitalWrite(MotorRightB, LOW);
}
void turnLeftSearch() {
  analogWrite(MotorLeftA, 50);
  digitalWrite(MotorLeftB, LOW);
  digitalWrite(MotorRightA, LOW);
  analogWrite(MotorRightB, 50);
}
void turnRightP() {
  digitalWrite(MotorLeftA, LOW);
  analogWrite(MotorLeftB, 210);
  digitalWrite(MotorRightA, LOW);
  analogWrite(MotorRightB, 200);
}
void turnLeftP()  {
  digitalWrite(MotorLeftA, LOW);
  analogWrite(MotorLeftB, 180);
  digitalWrite(MotorRightA, LOW);
  digitalWrite(MotorRightB, HIGH);
}
void goBackward() {
  analogWrite(MotorLeftA, 240);
  digitalWrite(MotorLeftB, LOW);
  analogWrite(MotorRightA, 220);
  digitalWrite(MotorRightB, LOW);
}

void goBackward1() {
  analogWrite(MotorLeftA, 140);
  digitalWrite(MotorLeftB, LOW);
  analogWrite(MotorRightA, 120);
  digitalWrite(MotorRightB, LOW);
}
void bturnRightP() {
  analogWrite(MotorLeftA, 190);
  digitalWrite(MotorLeftB, LOW);
  analogWrite(MotorRightA, 210);
  digitalWrite(MotorRightB, LOW);
}
void bturnLeftP() {
  analogWrite(MotorLeftA, 220);
  digitalWrite(MotorLeftB, LOW);
  analogWrite(MotorRightA, 190);
  digitalWrite(MotorRightB, LOW);
}
void bturnRight() {
  digitalWrite(MotorLeftA, LOW);
  analogWrite(MotorLeftB, 60);
  analogWrite(MotorRightA, 60);
  digitalWrite(MotorRightB, LOW);
}
void bturnLeft() {
  analogWrite(MotorLeftA, 60);
  digitalWrite(MotorLeftB, LOW);
  digitalWrite(MotorRightA, LOW);
  analogWrite(MotorRightB, 60);
}

long readfront(){ 
digitalWrite(USFrontTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(USFrontTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(USFrontTrigPin, LOW);
  long duration = pulseIn(USFrontEchoPin, HIGH);
  return microsecondsToCentimeters(duration);//H SUNARTHSH EPISTREFEI CM 
}

long readfrontleft(){ //SUNARTHSH GIA NA DIAVAZW TIMES APO TON DEKSI ULTRASONIC
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return microsecondsToCentimeters(duration);//H SUNARTHSH EPISTREFEI CM 
}

long readbackleft(){
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  long duration = pulseIn(echoPin2, HIGH);
  return microsecondsToCentimeters(duration);//H SUNARTHSH EPISTREFEI CM 
}

long readback(){  
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  long duration = pulseIn(echoPin3, HIGH); 
  return microsecondsToCentimeters(duration);//H SUNARTHSH EPISTREFEI CM 
}

long readbackright(){
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  long duration = pulseIn(echoPin4, HIGH);  
  return microsecondsToCentimeters(duration);//H SUNARTHSH EPISTREFEI CM 
}

long readfrontright(){
  digitalWrite(trigPin5, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin5, LOW);
  long duration = pulseIn(echoPin5, HIGH);
  return microsecondsToCentimeters(duration);//H SUNARTHSH EPISTREFEI C
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}


//PIN31
//PIN33
