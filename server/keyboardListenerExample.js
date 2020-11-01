/*******************************************************************
    In this example we will focus the cameras using macro keyboard commands

    Does not need an Arduino to Test, but to use with an Arudino you
    would emulate the key presses with a HID compatible Arudino such
    as the Pro Micro or ESP32 BLE.

    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

const camControl = require("./index");
const ioHook = require("iohook");

//Making sure Auto Focus is off for both
camControl.webcams.forEach((webcam, i) => {
  camControl.setAutoFocus(i, 0);
});

let activeWebcamIndex = 0;

ioHook.on("keydown", (event) => {
  //console.log(event);
  if (event.altKey && event.shiftKey && event.ctrlKey) {
    switch (event.rawcode) {
      case 38: //up
        camControl
          .adjustFocus(activeWebcamIndex, 5)
          .then(() => console.log("Focus Increased for " + activeWebcamIndex))
          .catch((err) => console.log(err));
        break;
      case 40: //down
        camControl
          .adjustFocus(activeWebcamIndex, -5)
          .then(() => console.log("Focus Decreased for " + activeWebcamIndex))
          .catch((err) => console.log(err));
        break;
      case 32: //space
      case 112: //F1
        activeWebcamIndex = (activeWebcamIndex + 1) % 2; // will toggle between 0 and 1
        break;
    }
  }
});

ioHook.start();
