#ifndef RS405CB_h
#define RS405CB_h

#include <Arduino.h>


class RS405CB {
  private:
    int txdenPin;
    int baudRate;
    int motorID;
    unsigned char sendbuf[32]; // Buffer for sending data
    unsigned char readbuf[32]; // Buffer for receiving data

  public:
    RS405CB(int bRate, int txdenPin, int id);
    void init(); // New initialization function
    void flashRom(int motorid);
    void reboot(int motorid);
    void changeID(int newMotorID);  
    void changeBrate(int newBaudRate);
    int move(int position, int time);
    void torque(int enable);
    int getAngle();
};

#endif


