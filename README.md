# Futuba_RS405CB
Arduino library to control futuba RS405CB with MAX485

![circuit](https://github.com/lastVIZSLA/Futuba_RS405CB/blob/main/circuit.png)

**Note:**

- The code uses "Serial1" for communicating with the MAX485 in Arduino Mega, with pins 19 and 18. Please adjust the communication pins according to the microcontroller you are using. Alternatively, you can change the #define serialPort Serial1 in the CPP file to the serial port you choose to use.

- If you are using the Futaba RS405CB for the first time, please use a baud rate of 115200 and set the motor ID to 1. These are the default factory values.

- ## How to Use

     - **Initialization:** (optional) Call the `init()` function after creating the motor object to initialize the motor:
     ```cpp
     myMotor.init();
     ```
     sets the torque High
   - **Flash ROM:** Use `flashRom()` to flash the ROM of a specified motor ID:
     ```cpp
     myMotor.flashRom(motorID);
     ```
   - **Reboot Motor:** Reboot a motor with the specified motor ID using `reboot()`:
     ```cpp
     myMotor.reboot(motorID);
     ```
   - **Change Motor ID:** Change the motor ID to a new ID using `changeID()`:
     ```cpp
     myMotor.changeID(newMotorID);
     ```
     change is permanent saves the value in flash rom and reboots the motor
   - **Change Baud Rate:** Change the baud rate to a new value using `changeBrate()`:
     ```cpp
     myMotor.changeBrate(newBaudRate);
     ```
     change is permanent saves the value in flash rom and reboots the motor
   - **Move Motor:** Use `move()` to move the motor to a specified position over a certain time:
     ```cpp
     myMotor.move(position, time);
     ```
   - **Control Torque:** Enable or disable torque using `torque()`:
     ```cpp
     myMotor.torque(enable);
     ```
   - **Get Current Angle:** Retrieve the current angle of the motor using `getAngle()`:
     ```cpp
     int currentAngle = myMotor.getAngle();
     '''
     TBD


