# C920-Arduino-Control

Several different ways of Controlling a Logitech C920 using an Arduino

There are two parts to this, a script running on your PC that can receive messages from the Arduino and then to control the webcam. The PC code _should_ work on Mac and Linux, but I have not tested it.

The webcam control part of this is making use of [node-uvc-control library by Joel Purra](https://github.com/joelpurra/node-uvc-control).

## Help support what I do!

I really enjoy creating open source Arduino projects that I hope people can make use of. [If you enjoy my work, please consider becoming a Github sponsor!](https://github.com/sponsors/witnessmenow/)

## Install

- Download and install [Node](https://nodejs.org/en/).
- Navigate to the "server" folder of this project on the commands line
- Type `npm install`, this will install this projects dependencies.
- Run the example you want by typing `node ./noArduinoExample.js` (change to whatever file is appropriate, see below)
- Press "CTRL + D" to stop running the code.

## PC Examples

Currently there are 4 PC examples

- NoArduinoExample.js - This sets the focus of the camera to one value and then another. It's a good one to start with to prove you can control the camera at all.
- SerialExample.js - This communicates with your Arduino over USB serial. Arduino should be running the "RotaryEncoderSerial" example.
- KeyBoardListenerExample.js - This listens for Macro Keyboard commands, so could be useful with an Arduino with HID capabilities. Use with "PicoPlanetHID" example. This could also be used with just a regular keyboard.
- WebserverExample.js - This sets up a webserver and listens for requests to change the focus. For use with "RotaryEncoderWeb" Arduino example

## Usage

```
const camControl = require("./index");

camControl.webcams // an array of webcams to control

camControl.setAutoFocus(cameraIndex, autoFocusValue) // sets autoFocus on/off
// cameraIndex: the index of the camera you want to control in webcams array
// autoFocusValue: 0 == off, 1 == on
//
// returns a promise that resolves when value has been set

//----------------
// Note:
// - Focus values can only be set when auto-focus is off
// - Very often the driver does not accept values that are not divisible by 5 (Don't know why)
//----------------

camControl.setFocus(cameraIndex, focusValue) // sets the focus value
// cameraIndex: the index of the camera you want to control in webcams array
// focusValue: the focus value you want to set (0-250, 0 being the least focused)
//
// returns a promise that resolves when value has been set

camControl.adjustFocus(activeWebcamIndex, focusAdjustment) // changes focus by adjustment amount
// cameraIndex: the index of the camera you want to control in webcams array
// focusAdjustment: will be added to the current focus value (use a negative adjustment to decrease)
//
// returns a promise that resolves when value has been adjusted

```

This is just a small subset of the properties that can potentially be changed, the original goal of the project was to just control focus. Check out [Joel's UVCC command line tool](https://github.com/joelpurra/uvcc) for more potential properties to change. Feel free to raise a github issue if there is another property you would like supported. PR's also welcome.

## Webcam support

Only tested with C920, but potentially works with others. (you will need to change the VID and PID in index.js)

Do not install logitech software/drivers, just plug in your webcam and let windows find the drivers. [Instructions here](https://blog.logitech.com/2018/01/03/multi-camera-streaming-with-logitech-webcams-a-how-to-guide/)
