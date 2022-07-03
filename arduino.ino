#include <SoftwareSerial.h>
#include <Arduino_JSON.h>
SoftwareSerial mySerial(7, 8); // RX, TX  //oposite
int M_B1 = 13; //motor a = + //in1
int M_B2 = 12; //motor a = - //in2
int M_A1 = 11; //motor b = - //in3
int M_A2 = 10; //motor b = + //in4
int x = 0;
int stopp = 0;
int speed_A = 5;
int speed_B =6;
String oldR = "aa";
String first = "A";
//positive motors have black mark in h-bridge
int R_S = A0; //sensor R
//int S_S = A1; //sensor S
int L_S = 3; //sensor L

String str;
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
pinMode(M_B1, OUTPUT);
pinMode(M_B2, OUTPUT);
pinMode(M_A1, OUTPUT);
pinMode(M_A2, OUTPUT);
pinMode(M_A2, OUTPUT);

pinMode(speed_A, OUTPUT);
pinMode(speed_B, OUTPUT);
analogWrite(speed_A, 130); 
analogWrite(speed_B, 130); 
mySerial.begin(115200);

pinMode(L_S, INPUT);
//pinMode(S_S, INPUT);
pinMode(R_S, INPUT);
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
        Stop();
          if(dir == "r"){
          //moto should go right
          turnRight();
          delay(7000);
            y --;    
        }
        else{
         
          //motor should go left
          turnLeft();
          delay(7000);
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
          //go to the shelf place and put it in its place (lefting) then x = -1
          //back to point of start
          while(1){
            Stop();
          }
          
        }
        if(x == -1){
           //start back to orgin 
      int x2 = myObject["x"];
      int y2 = myObject["y"];
     const char* dir2 = myObject["direction"];
      if(y2 > 0){
        //moto go straight
        //qr run to lower the y2 every time till y2 = 0
      }
      if(y2 == 0){
        //stop the motor
        if(dir2 == 'l'){
          //rotate to right
          y2--;
        }
        else{
          //rotate to left
          y2--;
        }
      }
      if(y2 == -1){
        if(x2 > 0){
          //motor go straight 
        }
        else{
          //stop the motor
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
void forword(){
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);
Serial.println("Forward");  
}
  

void turnRight(){

digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);
Serial.println("Right"); 
}

void turnLeft(){
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);  
Serial.println("Left");   
}


void Left(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);
Serial.println("Right");   
}


void Right(){
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH);
Serial.println("left"); 
}

void Stop(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
Serial.println("stop"); 
}
void FollowLine(){
if ((digitalRead(L_S) == 0)&&(digitalRead(R_S) == 0)){forword();}
if ((digitalRead(L_S) == 1)&&(digitalRead(R_S) == 0)){Left();}
if ((digitalRead(L_S) == 0)&&(digitalRead(R_S) == 1)){Right(                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  );}
}
