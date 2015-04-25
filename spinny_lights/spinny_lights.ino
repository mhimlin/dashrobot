/*
This sample code will make the robot turn on its lights if it senses low light,
 the robot will see light that is bright and will dance,
 the robot will see if something is in front of him and will back up. 
 Author: Madeline Himlin for North Ranch Elementary School Science Fair
 spinny lights by Madeline Himlin is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License. */

//Libraries
#include <EEPROM.h>
#include <DashBot.h>

DashBot rex; //Gyro, motors, controller, LEDs, eyes

float L_motor = 0; //Value for Left Motor
float R_motor = 0; //Value for Right Motor

void setup() {
  rex.dashRadioSetup();
  Serial.begin(9600);
}

void loop(){

  int readLight=0;
  //read lights if low light will set eye color to light blue
  readLight =rex.readAmbientLight();
  Serial.println(readLight);
  if(readLight < 25){
    rex.setEyeColor(23,176,227);
  }
  else if(readLight > 500){ //if light bright will set eye color light red
    rex.setEyeColor(234,75,89);
    //Dance code here
    //will dance and spin in circles
    unsigned long init_time = millis();

    while (millis()- init_time < 1000){
      rex.motorDriveL(-80);
      rex.motorDriveR(80);
      rex.setEyeColor(0,100,0);
    }

    while (millis()- init_time < 2000){
      rex.motorDriveL(-80);
      rex.motorDriveR(80);
      rex.setEyeColor(100,0,0);
    }

    while (millis()- init_time < 3000){
      rex.motorDriveL(80);
      rex.motorDriveR(-80);
      rex.setEyeColor(0,0,100);
    }

    while (millis()-init_time < 4000){
      rex.motorDriveL(80);
      rex.motorDriveR(-80);
      rex.setEyeColor(126,255,89); 
    }

    rex.allStop();
    //end dance code
  }
  else{ //if light is normal
    //if something in front will back up
    if (rex.detectCollisionLeft(25) || rex.detectCollisionRight(25)){
      rex.dashRun(-30,0);
      delay(500);
    }
    //stop and turn lights off
    rex.allStop(); 
    rex.setEyeColor(0,0,0);
  } 
}


