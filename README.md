Scream.  I am Scream.

Lightning McScream, a custom battery-powered racecar and AR race track, driven by screams.

## Inspiration
Inspired by the delightful shrieks of circuses, Lightning McScream brings the thrill of racing to life in a unique way. The concept for a scream-powered car was inspired by the fact that joy can fuel competition; the louder you scream, the faster your car goes. With a laser-cut design and electronics controlled by an ESP32 microcontroller, Lightning McScreem converts your voice into velocity. Set on an augmented reality track, Lightning McScream allows you to experience the exhilarating connection between sound and speed.

## What it does
Lightning McScream is a real-world and virtual game experience where the user screams to control the speed at which their car races along a user-defined virtual reality drag race, competing to achieve the best time and speeds using nothing more than the power of their own voice.

## How we built it
**Augmented Reality (AR) User Interface (Oculus Quest 2)**
- Unity was used to create custom-made game assets, such as the racing track boundaries, track, and menus.

**Software (C++, C#)**
- An audio processing algorithm was developed using Python and C# in order to record user input and environmental noise in real time and convert these signals to integer values representing volume and pitch, which were subsequently used to control the speed of the car.
- A web server was constructed using FastAPI in order to transmit the audio signals collected by the Oculus to the microcontroller, which controls the rotational speed of the back axel.
- An algorithm was also written to process accelerometer and position data to determine car’s location and duration of run, and identify maximum speed achieved by the car.

**Embedded Systems (ESP32 Microcontroller)**
- The car and all onboard electronics are controlled via an ESP32 microcontroller.  Arduino Nanos were also used in the testing process to assess audio processing and motor functionality. 
- The ESP32 microcontroller also controls power to the DC motor, motor driver, and other onboard electronics.

**Electronics (DC motor, motor driver, batteries, servo)**
- RobotZone Mini-Econ Gear Motors for two back wheels
- Accelerometer to detect acceleration in x,y,z coordinates in order to identify position and top speed
- L298N DC Relay to interface motor with ESP microcontroller
- Custom designed 12V battery supply to power car devices
- MG996 Servo to rotate front axel for steering

**Car**
- The car frame was designed from scratch and assembled out of laser cut parts.
- The two gears were custom designed with a 30:10 ratio and laser cut from particle board to transfer motor rotation to axel rotation
- The axels and wheels were both custom made and LEGO.

## Challenges we ran into
- Powering and controlling the car remotely were the two main challenges.
- The car is powered by a custom-designed 12V power supply, which was chosen to power all of the electronics and controls on board the car.  There were issues with loading and voltage spiking, so we had to ensure that the proper voltage and power levels were being properly delivered.
- Our original plan was to use Bluetooth for communication between the car and the Oculus that was connecting audio signals from the user.  However, the Bluetooth modules that interfaced with the Arduino Nano were too slow and did not provide the real-time feedback desired.  We switched from using this Arduino Nano to an ESP 8266 microcontroller, which includes onboard Bluetooth and WiFi.

## What's next for Lightning McScream
Screaming.
