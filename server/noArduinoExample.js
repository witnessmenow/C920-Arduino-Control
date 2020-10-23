/* --------------------------

This is a good example to start with as you can prove you can control your Webcam
at all.

It will turn off auto-focus on all connected cameras and then adjust their
focus.

-----------------------------*/
const camControl = require("./index");
const sleep = (waitTimeInMs) =>
  new Promise((resolve) => setTimeout(resolve, waitTimeInMs));

const focusTester = function (cameraIndex) {
  console.log("-----------------------------------------");
  console.log("Focus Testing Camera " + cameraIndex);
  console.log("-----------------------------------------");
  return camControl
    .setAutoFocus(cameraIndex, 0)
    .then(() => camControl.setFocus(cameraIndex, 100))
    .then(() => sleep(2000))
    .then(() => camControl.setFocus(cameraIndex, 0));
};

// TODO: Get Good at promises
// I should be building the promises from the length of webcams, but that is actually harder than you would think!
// possible: https://stackoverflow.com/a/31070150
if (camControl.webcams.length >= 2) {
  focusTester(0)
    .then(() => sleep(2000))
    .then(() => focusTester(1))
    .catch((err) => {
      console.log(err);
    });
}
