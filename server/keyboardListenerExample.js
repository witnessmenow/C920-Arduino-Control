/* --------------------------

In this example we will focus the cameras using hot keys

Does not need an Arduino to Test, but to use with an Arudino you
would emulate the key presses with a HID compatible Arudino such
as the Pro Micro or ESP32 BLE

-----------------------------*/
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
        activeWebcamIndex = (activeWebcamIndex + 1) % 2; // will toggle between 0 and 1
        break;
    }
  }
});

ioHook.start();
