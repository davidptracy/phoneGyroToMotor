/* Control a servo motor with your phone's gyro sensor
 by David Tracy 
 http://www.davidptracy.com
 created Nov 9 2014 
 
 This code requires an arduino Yun with node and node ws installed and expanded disk space:
 http://www.tigoe.com/pcomp/code/arduinowiring/1216/
 
 See the github repo below for server and client code:
 https://github.com/davidptracy/phoneGyroToMotor

 Client code must be copied to the node folder listed in setup to the micro SD for this to work 
 correctly. 

 This example code is in the public domain. 
*/ 

#include <Bridge.h>
#include <Process.h>
#include <Servo.h>   

// make a new Process for calling Node
Process p; 

// creates an instance of the servo object to control a servo
Servo servoMotor;       
// Control pin for servo motor
int servoPin = 9;      

void setup() {
  
  // initialize bridge and serial
  Serial.begin(9600);

  //don't start the sketch until the serial monitor is up and running  
  while(!Serial);
  Bridge.begin();
  
  Serial.println("========== PROCESS INITIATED ==========");
  Serial.println("======= WAITING FOR GYRO VALUES =======");
  
  // launch the echo.js script asynchronously:
  p.runShellCommandAsynchronously("killall node");
  p.runShellCommandAsynchronously("node /mnt/sda1/arduino/node/wsArduinoServer.js");
  
  // connect the servo motor to pin 9
  servoMotor.attach(9);
    
}

void loop() {  
  
  // read the characters coming in from linux the linux process until you get a carriage return
  // cast those values into a string
  String sensorStr = p.readStringUntil('\n');
  
  // convert the string into an integer
  int sensorVal = sensorStr.toInt();
  
  // remap integer values from the phone to a useable range by the servo
  int servoAngle = map(sensorVal, -180, 180, 0, 179);
  // print the servo angle to serial
  Serial.println(servoAngle);
  
  // move the servo using the angle from the sensor:
  servoMotor.write(servoAngle); 

}
