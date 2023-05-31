
// Copyright 2021 Michael Floren (Seafoxc)
// https://www.youtube.com/c/seafoxc
// Date 23/05/2021 
// Version 2.0



#include "Factory_IO.h"
bool motor1 = HIGH;
bool motor2 = HIGH;
bool moveZ = LOW;
bool moveX = LOW;
bool detectado = LOW;
bool Grab = LOW;
bool sensor1 = LOW;
bool sensorZ = LOW;
bool sensorX = LOW;
bool sensor2 = LOW;
bool sensor3 = LOW;
bool sensor4 = LOW;

bool estadoButton = 0;

void setup()
{   
   FactoryIO_Setup(); 
   pinMode(LED_D0, OUTPUT);
   pinMode(A0, INPUT);

   
}



void loop()
{
    
    FactoryIO_ReadInputs();    // Reading the inputs from Factory I/O

    

//--------------------------------------------------------------------------------------------------------
//-------------------------- Here you have place to write your Main program ------------------------------
//--------------------------------------------------------------------------------------------------------
// Digital Inputs : FactoryIO_Input0 , FactoryIO_Input1 ,.....,  FactoryIO_Input15
// Digital Outputs: FactoryIO_Coil0 , FactoryIO_Coil1, ..... , FactoryIO_Coil15
// Analog Inputs : FactoryIO_InputReg0, FactoryIO_InputReg1, ..... , FactoryIO_InputReg7
// Analog Outputs : FactoryIO_HoldingReg0, FactoryIO_HoldingReg1, ..... , FactoryIO_HoldingReg7
// Logic for scene "2 - from A to B (Set en Reset)  

 
 
  detectado = FactoryIO_Input0;
  sensor1 = FactoryIO_Input1;
  sensorZ = FactoryIO_Input2;
  sensorX = FactoryIO_Input3;
  sensor2 = FactoryIO_Input11;
  sensor3 = FactoryIO_Input4;
  sensor4 = FactoryIO_Input12;


estadoButton = digitalRead(A0);
if (estadoButton == HIGH){
   if (sensor1 == HIGH && sensor2 == LOW){ // Sensor is low when a box is between the sensor and the reflector of the sensor
     motor1 = LOW;
     moveZ = HIGH;
     Grab = HIGH;
  }else{
    Grab = LOW;
    motor1 = HIGH;
    moveZ = LOW;
  }
  
  if (detectado == HIGH && sensor2 == LOW){
    moveZ = LOW;
    moveX = HIGH;
    Grab = HIGH;
  }else{
    Grab = LOW;
  }

  if (sensor2 == HIGH){
    moveZ = HIGH;
    Grab = HIGH;
    motor2 = LOW;
  }else{
    motor2 = HIGH;
  }
  
  if (sensor2 == HIGH && sensor3 == HIGH){
    Grab = LOW;
    moveZ = LOW;
    moveX = LOW;
  }
}else{
  motor1 = LOW;
  motor2 = LOW;
}



 

  

  // Writing Outputs 

  FactoryIO_Coil0 = motor1;
  FactoryIO_Coil1 = motor2;
  FactoryIO_Coil2 = moveZ;
  FactoryIO_Coil3 = moveX;
  FactoryIO_Coil4 = Grab;

  
  FactoryIO_WriteOutputs();    // Writing the outputs to Factory I/O
  
}
