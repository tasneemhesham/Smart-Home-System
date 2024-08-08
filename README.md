# Smart Home Project

## Overview

This Smart Home project integrates multiple sensors and actuators to automate various aspects of home management and security. The system includes:

- **Ultrasonic Sensor** for opening the main gate with servo motors.
- **PIR Sensor** for opening the garage door with a servo motor.
- **Gas Sensor** for detecting gas leaks in the kitchen.
- **Ultrasonic Sensor** for turning on the light in the bedroom.
- **Water Level Sensor** with an LCD display in the garden.
- **LDR Sensors** for adjusting solar panel angles on the floor.
- **RFID Reader** for detecting RFID tags, sending signals to an MP3 player, and activating a switch to move the elevator.

## Components

1. **Ultrasonic Sensor (Main Gate)**
   - **Function**: Measures distance to control the opening of the main gate.
   - **Action**: Uses a servo motor to open the gate based on distance measurements.

2. **PIR Sensor (Garage)**
   - **Function**: Detects motion to control the garage door.
   - **Action**: Uses a servo motor to open the garage door when motion is detected.

3. **Gas Sensor (Kitchen)**
   - **Function**: Detects gas leaks in the kitchen.
   - **Action**: Triggers a buzzer and sends a warning message if gas levels exceed a set threshold.

4. **Ultrasonic Sensor (Bedroom)**
   - **Function**: Measures distance to control lighting in the bedroom.
   - **Action**: Turns on the light if an object is detected within a specified distance.

5. **Water Level Sensor (Garden)**
   - **Function**: Monitors water level and displays it on an LCD.
   - **Action**: Categorizes water levels as "Empty", "LOW", "Medium", or "HIGH" and displays the information on the LCD.

6. **LDR Sensors (Solar Panel)**
   - **Function**: Measures light intensity to adjust solar panel angles.
   - **Action**: Adjusts the solar panel's angle to optimize energy capture based on light intensity.

7. **RFID Reader (Elevator and MP3 Player)**
   - **Function**: Detects RFID tags and controls the elevator and MP3 player.
   - **Action**: Sends signals to the MP3 player and activates a switch to move the elevator when an RFID tag is detected.

## Setup

1. **Wiring:**
   - Ensure all sensors and actuators are properly connected to the Arduino or respective controllers.

2. **Libraries:**
   - `Servo.h` for controlling servos.
   - `LiquidCrystal_I2C.h` for LCD display.
   - `RFID.h` for RFID functionality.
   - `LDR.h` for solar panel control.

## Code Functionality

1. **Main Gate Operation:**
   - Uses an ultrasonic sensor to measure distance and control a servo motor to open the gate.

2. **Garage Door Operation:**
   - Uses a PIR sensor to detect motion and control a servo motor to open the garage door.

3. **Gas Detection:**
   - Reads values from a gas sensor and activates a buzzer if gas levels are high.

4. **Bedroom Lighting:**
   - Uses an ultrasonic sensor to detect objects and turn on the bedroom light.

5. **Water Level Monitoring:**
   - Reads the water level sensor and displays the level on an LCD.

6. **Solar Panel Adjustment:**
   - Uses LDR sensors to measure light intensity and adjust the solar panel angle for optimal energy capture.

7. **RFID Functionality:**
   - Detects RFID tags, sends signals to an MP3 player, and activates a switch to move the elevator.

## Usage

1. **Upload Code:**
   - Connect your Arduino board or controllers to your computer.
   - Open the Arduino IDE, paste the code, and upload it to the board.

2. **Monitor:**
   - Open the Serial Monitor to view output messages and sensor readings.

## Notes

- Adjust the thresholds and settings as needed for your specific setup.
- Ensure all components are properly installed and calibrated.
