# C920-Arduino-Control

Controlling a Logitech C920 (focus) using an Arduino

There are two parts to this, a script running on your PC that can receive messages from the Arduino and then to control the webcam

Currently there are 3 PC examples

- NoArduinoExample.js - This sets the focus of the camera to one value and then another. It's a good one to start with to prove you can control the camera at all
- SerialExample.js - This communicates with your Arduino over USB serial. Arduino should be running the "RotaryEncoderSerial" example.
- KeyBoardListenerExample.js - This listens for Macro Keyboard commands, so could be useful with an Arduino with HID capabilities. Use with "PicoPlanetHID" example.

Only tested with C920. Do not install logitech software/drivers, just plug in your webcam and let windows find the drivers. [Instructions here](https://blog.logitech.com/2018/01/03/multi-camera-streaming-with-logitech-webcams-a-how-to-guide/)

## Install

- Download and install [Node](https://nodejs.org/en/).
- Navigate to the "server" folder of this project on the commands line
- Type `npm install`, this will install this projects dependencies.
- Run the example you want by typing `node ./noArduinoExample.js` (change to whatever file is appropriate)
