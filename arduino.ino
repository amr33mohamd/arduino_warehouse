#include <SoftwareSerial.h>
#include <Arduino_JSON.h>

String str;
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
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
    if(type == "add"){
      if(y > 0){
        //motor shoud go straight 
        //qr should run and lower the y every time reads qr and stop when y = 0
      }
      if(y == 0){
        //stop the motor
        if(dir == "r"){
          y --;
          //moto should go right
        }
        else{
          y--;
          //motor should go left
        }
       
      }
      if(y == -1){
         //qr should run and lower the x every time reads qr and stop when x = 0
        if(x > 0){
        //motor shoud go straight 
        }
        if(x == 0){
          //go to the shelf place and put it in its place (lefting) then x = -1
          //back to point of start
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
