#include "RS405CB.h"
#include <Arduino.h>

#define serialPort Serial1


RS405CB::RS405CB( int bRate, int txdenPin, int id) :  baudRate(bRate), txdenPin(txdenPin), motorID(id) {
  
  init(); // Call the init function when an instance is created
}

void RS405CB::init() {
  Serial.begin(9600); // Initialize serial monitor
  Serial.println("RS405CB initiating.");
  //Serial.println(baudRate);
  //Serial.begin(9600);
  pinMode(txdenPin, OUTPUT);
  digitalWrite(txdenPin, HIGH); 
  serialPort.begin(baudRate);
  torque(1);
  Serial.println("RS405CB initialized.");
}

void RS405CB::flashRom(int motorid) {
  // Implementation of flashing ROM
  unsigned char sum;

  sendbuf[0] = (unsigned char) 0xFA;
  sendbuf[1] = (unsigned char) 0xAF; 
  sendbuf[2] = (unsigned char) motorid;
  sendbuf[3] = (unsigned char) 0x40; 
  sendbuf[4] = (unsigned char) 0xFF; 
  sendbuf[5] = (unsigned char) 0x00; 
  sendbuf[6] = (unsigned char) 0x00; 

  sum = sendbuf[2];
  for (int i = 3; i < 7; i++) {
    sum = (unsigned char)(sum ^ sendbuf[i]);
  }
  sendbuf[7] = sum;

 
  digitalWrite(txdenPin, HIGH);

  serialPort.write(sendbuf,8);
  
  delay(50);
  digitalWrite(txdenPin,LOW);

}

void RS405CB::reboot(int motorid) {
  // Implementation of rebooting motor

  unsigned char sum;


  sendbuf[0] = (unsigned char) 0xFA; 
  sendbuf[1] = (unsigned char) 0xAF; 
  sendbuf[2] = (unsigned char) motorid; 
  sendbuf[3] = (unsigned char) 0x20; 
  sendbuf[4] = (unsigned char) 0xFF; 
  sendbuf[5] = (unsigned char) 0x00;
  sendbuf[6] = (unsigned char) 0x00; 


  sum = sendbuf[2];
  for (int i = 3; i < 7; i++) {
    sum = (unsigned char)(sum ^ sendbuf[i]);
  }
  sendbuf[7] = sum; 


  digitalWrite(txdenPin, HIGH);

  serialPort.write(sendbuf,8);
  delay(50);
  digitalWrite(txdenPin, LOW);

}

void RS405CB::changeID(int newMotorID) {
  // Implementation of changing motor ID

  unsigned char sum;

  sendbuf[0] = (unsigned char) 0xFA; 
  sendbuf[1] = (unsigned char) 0xAF; 
  sendbuf[2] = (unsigned char) motorID; 
  sendbuf[3] = (unsigned char) 0x00; 
  sendbuf[4] = (unsigned char) 0x04; 
  sendbuf[5] = (unsigned char) 0x01; 
  sendbuf[6] = (unsigned char) 0x01; 
  sendbuf[7] = (unsigned char) newMotorID; 


  sum = sendbuf[2];
  for (int i = 3; i < 8; i++) {
    sum = (unsigned char)(sum ^ sendbuf[i]);
  }
  sendbuf[8] = sum; 
  
  digitalWrite(txdenPin, HIGH);

  serialPort.write(sendbuf,9);
  
  delay(50);
  digitalWrite(txdenPin, LOW);
  flashRom(newMotorID);
  reboot(newMotorID);
}

void RS405CB::changeBrate(int newBaudRate) {
  unsigned char sum;

  sendbuf[0] = (unsigned char) 0xFA; 
  sendbuf[1] = (unsigned char) 0xAF; 
  sendbuf[2] = (unsigned char) motorID; 
  sendbuf[3] = (unsigned char) 0x00; 
  sendbuf[4] = (unsigned char) 0x06; 
  sendbuf[5] = (unsigned char) 0x01; 
  sendbuf[6] = (unsigned char) 0x01; 
  sendbuf[7] = (unsigned char) 0x00; 



  // チェックサムの計算
  sum = sendbuf[2];
  for (int i = 3; i < 8; i++) {
    sum = (unsigned char)(sum ^ sendbuf[i]);
  }
  sendbuf[8] = sum;// チェックサム

  // 送信
  digitalWrite(txdenPin, HIGH);

  serialPort.write(sendbuf,9);
  
  delay(50);//送信が終わるまで待つ
  digitalWrite(txdenPin,LOW);
  flashRom(motorID);
  reboot(motorID);
}

int RS405CB::move(int position, int time) {
  // Implementation of moving the motor

  unsigned char sum;
  
  //Serial.println("HI");
  sendbuf[0] = (unsigned char) 0xFA; 
  sendbuf[1] = (unsigned char) 0xAF; 
  sendbuf[2] = (unsigned char) motorID;
  sendbuf[3] = (unsigned char) 0x00; 
  sendbuf[4] = (unsigned char) 0x1E; 
  sendbuf[5] = (unsigned char) 0x04; 
  sendbuf[6] = (unsigned char) 0x01; 
  sendbuf[7] = (unsigned char) (position & 0x00FF); 
  sendbuf[8] = (unsigned char) ((position & 0xFF00) >> 8); 
  sendbuf[9] = (unsigned char) (time & 0x00FF); 
  sendbuf[10] = (unsigned char) ((time & 0xFF00) >> 8); 

  sum = sendbuf[2];
  for (int i = 3; i < 11; i++) {
    sum = (unsigned char)(sum ^ sendbuf[i]);
  }
  sendbuf[11] = sum; 
  digitalWrite(txdenPin, HIGH);

  serialPort.write(sendbuf,12);
  
  delay(50);
  digitalWrite(txdenPin,LOW);
  return 1;
}

void RS405CB::torque(int enable) {
    unsigned char sum;

    
    sendbuf[0] = (unsigned char) (0xFA); 
    sendbuf[1] = (unsigned char) (0xAF); 
    sendbuf[2] = (unsigned char) (motorID); 
    sendbuf[3] = (unsigned char) (0x00); 
    sendbuf[4] = (unsigned char) (0x24); 
    sendbuf[5] = (unsigned char) (0x01); 
    sendbuf[6] = (unsigned char) (0x01); 
    sendbuf[7] = (unsigned char)(((enable)&0x00FF)); 

    
    sum = sendbuf[2];
    for (int i = 3; i < 8; i++) {
      sum = (unsigned char) (sum ^ sendbuf[i]);
    }
    sendbuf[8] = sum; 

    digitalWrite(txdenPin, HIGH);
    
    serialPort.write(sendbuf,9);


    delay(50);
    digitalWrite(txdenPin, LOW);

}

int RS405CB::getAngle() {
  // Implementation of getting motor angle
  return 0; // Placeholder return value
}



