
#include <RS405CB.h>
#define serialPort Serial1
#include <Arduino.h>


int txdenPin = 13; // TXDEN pin of RS485
int motorID1 = 1;  // ID of the RS405CB motor
int motorID2 = 2;  // ID of the RS405CB motor

// Create an instance of the RS405CB class


void setup() {

RS405CB myMotor( 9600, txdenPin, motorID1);
RS405CB myMotor1( 9600, txdenPin, motorID2);
while(1){
  myMotor.move(500, 100); // Move to position 1000 in 500 milliseconds
  delay(2000);
  myMotor.move(0, 100); 
  delay(2000);
  myMotor1.move(500, 100); // Move to position 1000 in 500 milliseconds
  delay(2000);
  myMotor1.move(0, 100); 
  delay(2000);
}

}


