/*******************************************************************
    In this example we will see how to receive commands via a serial port

    This should be paired with the Arduino Sketch "RotaryEncoderSerial"

    You will need to update this example with the COM port of your Arduino

    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

const camControl = require("./index");

const comPort = "COM6"; //Could be '/dev/tty-usbserial1' on mac
const baudRate = 115200; //Needs to match the sketch

const SerialPort = require("serialport");
const port = new SerialPort(comPort, { baudRate }, function (err) {
  if (err) {
    return console.log("Error: ", err.message);
  }
});

//Making sure Auto Focus is off for both
camControl.webcams.forEach((webcam, i) => {
  camControl.setAutoFocus(i, 0);
});

port.on("readable", function () {
  const inputData = port.read().toString();
  const inputArray = inputData.split(",");
  if (inputArray.length === 3) {
    const command = inputArray[0];
    const camIndex = parseInt(inputArray[1]);
    const value = parseInt(inputArray[2]);
    console.log(inputData);
    switch (command) {
      case "adj":
        camControl
          .adjustFocus(camIndex, value)
          .then(() => console.log("Focus Adjusted"))
          .catch((err) => console.log(err));
        break;
      case "auto":
        camControl
          .setAutoFocus(camIndex, value)
          .then(() => console.log("Auto Focus Updated"))
          .catch((err) => console.log(err));
        break;
    }
  }
});
