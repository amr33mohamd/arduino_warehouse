#include <SoftwareSerial.h>
#include <Arduino_JSON.h>
SoftwareSerial mySerial(7, 8); // RX, TX  //oposite

const int lineFollowSensor0 = A0;
const int lineFollowSensor1 = A1;
const int lineFollowSensor2 = A2;
const int lineFollowSensor3 = A3;
const int lineFollowSensor4 = A4;
int LFSensor[5]={0, 0, 0, 0, 0};

const int S_A = 5;  //speed motor a
int M_B1 = 13; //motor a = + //in1
int M_B2 = 12; //motor a = - //in2
int M_A1 = 11; //motor b = - //in3  
int M_A2 = 10; //motor b = + //in4
const int S_B = 6;  //speed motor b

int rspeed;
int lspeed;
const int speed_motor = 255;


float Kp = 5; // dummy
float Ki = 0; //dummy
float Kd = 15; //(Kp-1)*10
int error=0;
int previousError=0;
int P=0;
int I=0;
int D=0;
int PIDvalue;
int current_time;
int prev_time =0;
int elapsed_time=0;
int x = 0;
int stopp = 0;

String oldR = "aa";
String first = "A";
//positive motors have black mark in h-bridge


String str;
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
 pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);
  pinMode(lineFollowSensor4, INPUT);

  pinMode(M_B1, OUTPUT);
  pinMode(M_B2, OUTPUT);
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
  pinMode(S_B, OUTPUT);
  pinMode(S_A, OUTPUT);
  
mySerial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over

if (Serial.available()) {
    String incomingString = Serial.readStringUntil('|');
     JSONVar myObject = JSON.parse(incomingString);
if (myObject.hasOwnProperty("orders")) {
int orders = myObject["orders"];
  if(orders == 1){
     const char* type = myObject["type"];
     int x = myObject["x"];
     int y = myObject["y"];
      const char* dir = myObject["direction"];
    
    //add logic
    if(strcmp(type, "add") == 0){
      if(y > 0){
        //motor shoud go straight 
        while(y >0){
        FollowLine();
        if (mySerial.available()) {
          Serial.write(mySerial.read());
             first = mySerial.readString();
            if(first != oldR){
              y = y-1;
                Serial.print("y =");
                  Serial.println(y);
                      
                oldR = first;
         
            }
        }
        }
        //qr should run and lower the y every time reads qr and stop when y = 0
      }
      if(y == 0){
        //stop the motor
//        Stop();
//        delay(2000);
          if(dir == "r"){
          //moto should go right
          rotatRight();
          delay(1500);
            y --;    
        }
          else{
//         Stop();
//        delay(2000);
          //motor should go left
          rotatLeft();
          delay(1500);
           y--;
        }
       
      }
      if(y == -1){
         //qr should run and lower the x every time reads qr and stop when x = 0
         
        if(x > 0){
        //motor shoud go straight 
         Serial.print("x =");
                  Serial.println(x);
        while(x > 0){
        FollowLine();
        if (mySerial.available()) {
          Serial.write(mySerial.read());
             first = mySerial.readString();
              Serial.print("x =");
                  Serial.println(x);
            if(first != oldR){
              x = x-1;
                Serial.print("x =");
                  Serial.println(x);
                      
                oldR = first;
         
            }
        }
        }
        
        }

        if(x == 0){
          if(dir == 'l'){
          rotatRight(); //problem
          delay(2000);
        }
        else{
          rotatLeft(); //problem
          delay(2000);
          
        }
          
        }
        while(x > -2){
          //go to the shelf place and put it in its place (lefting) then x = -1
          //back to point of start
          //going to product 
           
           FollowLine();
           //read the product
          if (mySerial.available()) {
          Serial.write(mySerial.read());
             first = mySerial.readString();
              Serial.print("x =");
                  Serial.println(x);
            if(first != oldR){
              x = x-1;
                Serial.print("x =");
                  Serial.println(x);
                      
                oldR = first;
         
            }
        }         
        }
        if(x == -2){

          //stop when find the product
                Stop();
                delay(2000);
                //start lifing here 
                
                 //360 degree to back 
                 rotatRight();
                 delay(3000);
                 
        }
        while(x == -2){

          FollowLine();
 if (mySerial.available()) {
          Serial.write(mySerial.read());
             first = mySerial.readString();
              Serial.print("x =");
                  Serial.println(x);
            if(first != oldR){
              x = x-1;
                Serial.print("x =");
                  Serial.println(x);
                      
                oldR = first;
         
            }
        } 
        }
        if(x == -3){
          if(dir == 'l'){
            turnLeft();
          delay(1200);
        }
        else{
          turnRight();
          delay(1200);
        }
          
           //start back to orgin 
      int x2 = myObject["x"];
      int y2 = myObject["y"];
     const char* dir2 = myObject["direction"];
      if(x2 > 0){
        x2--;
        //motor shoud go straight 
         Serial.print("x =");
                  Serial.println(x);
        while(x2 > 0){
        FollowLine();
        if (mySerial.available()) {
          Serial.write(mySerial.read());
             first = mySerial.readString();
              Serial.print("x =");
                  Serial.println(x);
            if(first != oldR){
              x2 = x2-1;
                Serial.print("x =");
                  Serial.println(x2);
                      
                oldR = first;
         
            }
        }
        }
      }
        if(x2 == 0){
  
          if(dir == "r"){
          //moto should go right
          delay(1000);
          rotatLeft();
          delay(1500);
            x2 --;    
        }
          else{
          delay(1000);
          //motor should go left
          rotatRight();
          delay(1500);
           x2--;
        }
       
      }
      if(x2 == -1){
         //qr should run and lower the x every time reads qr and stop when x = 0
         
        if(y2 > 0){
        //motor shoud go straight 
         Serial.print("x =");
                  Serial.println(x);
                  y2--;
        while(y2 > 0){
        FollowLine();
        if (mySerial.available()) {
          Serial.write(mySerial.read());
             first = mySerial.readString();
              Serial.print("x =");
                  Serial.println(x);
            if(first != oldR){
              y2 = y2-1;
                Serial.print("x =");
                  Serial.println(x);
                      
                oldR = first;
         
            }
        }
        }
        
        }
        if(y2 == 0 ){
          while(1){
              Stop();
          }
        }
      }
      
      
     
      }
        
    }
    
    
  }
  
}
}

//if( incomingString ==  "Bre"){
//    Serial.print(myObject);
//}


}
}
 
//void turnRight(){
//
//digitalWrite(M_A1, LOW);
//digitalWrite(M_A2, LOW);
//digitalWrite(M_B1, HIGH);
//digitalWrite(M_B2, LOW);
//Serial.println("Right"); 
//}
//
//void turnLeft(){
//digitalWrite(M_A1, HIGH);
//digitalWrite(M_A2, LOW);
//digitalWrite(M_B1, LOW);
//digitalWrite(M_B2, LOW);  
//Serial.println("Left");   
//}


void forword(int error){
  rspeed = speed_motor + calculatePID(error);
  lspeed = speed_motor - calculatePID(error);

  //restricting speeds of motors between 255 and -255
  
    if (rspeed > 255) 
      rspeed = 255;
      
    if (lspeed > 255) 
      lspeed = 255;
      
    if (rspeed < -255) 
      rspeed = -255;
      
    if (lspeed < -255) 
      lspeed = -255;
 
analogWrite(S_A , rspeed);
analogWrite(S_B , lspeed); 
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
  Serial.println("Forward");  
}


void Right(int error){
 rspeed = speed_motor + calculatePID(error);
  lspeed = speed_motor - calculatePID(error);

  //restricting speeds of motors between 255 and -255
  
    if (rspeed > 255) 
      rspeed = 255;
      
    if (lspeed > 255) 
      lspeed = 255;
      
    if (rspeed < -255) 
      rspeed = -255;
      
    if (lspeed < -255) 
      lspeed = -255;
 
analogWrite(S_A , rspeed);
analogWrite(S_B , lspeed);
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, LOW);
Serial.println("Right");   
  
}


void Left(int error){
 rspeed = speed_motor + calculatePID(error);
  lspeed = speed_motor - calculatePID(error);

  //restricting speeds of motors between 255 and -255
  
    if (rspeed > 255) 
      rspeed = 255;
      
    if (lspeed > 255) 
      lspeed = 255;
      
    if (rspeed < -255) 
      rspeed = -255;
      
    if (lspeed < -255) 
      lspeed = -255;
 
analogWrite(S_A , rspeed);
analogWrite(S_B , lspeed);
digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
  Serial.println("left"); 
}
void turnLeft(){
analogWrite(S_A , 200);
analogWrite(S_B , 200);
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
Serial.println("Right");  
  }
  
void turnRight(){
analogWrite(S_A , 200);
analogWrite(S_B , 200);
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, LOW);
Serial.println("RIGHT"); 
}  


int calculatePID(int error)
{
  
  current_time = millis();
  elapsed_time = current_time - prev_time;
 
  P = error;
  I = I + error;
  D = (error-previousError)/elapsed_time;
  PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
  previousError = error;
  prev_time = current_time;
  return PIDvalue;
}

void Stop(){
digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, LOW);
Serial.println("stop"); 
}

void rotatRight(){
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, HIGH);
  }
  void rotatLeft(){
     digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, HIGH);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
    }

void FollowLine(){
LFSensor[0] = digitalRead(lineFollowSensor0);
LFSensor[1] = digitalRead(lineFollowSensor1);
LFSensor[2] = digitalRead(lineFollowSensor2);
LFSensor[3] = digitalRead(lineFollowSensor3);
LFSensor[4] = digitalRead(lineFollowSensor4);

if((LFSensor[0]== 0)&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1 )) {Left(4);}
else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1 )) {Left(3);} 
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1 )) {Left(2);}
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0)&&(LFSensor[2]== 0 ) &&(LFSensor[3]== 1 )&&(LFSensor[4]== 1 )) {Left(1);}

else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1 )) {forword(0);}
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 1 )) {forword(0);}

else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 1 )) {Right(-1);}
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 1 )) {Right(-4);}
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1) &&(LFSensor[3]== 0 )&&(LFSensor[4]== 0 )) {Right(-3);}
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 0 )) {Right(-4);}

}
