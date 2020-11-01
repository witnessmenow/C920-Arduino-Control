/* --------------------------

In this example we will see how to receive commands via a web request (over WiFi)

This should be paired with the Arduino Sketch "RotaryEncoderWeb"

-----------------------------*/
const camControl = require("./index");

const express = require("express");
const app = express();
const port = 3000;

//Who would have thought getting the IP address would be so much fun!
const ips = Object.values(require("os").networkInterfaces()).reduce(
  (r, list) =>
    r.concat(
      list.reduce(
        (rr, i) =>
          rr.concat((i.family === "IPv4" && !i.internal && i.address) || []),
        []
      )
    ),
  []
);

app.get("/adj", (req, res) => {
  const camIndex = parseInt(req.query.camIndex);
  const value = parseInt(req.query.value);
  camControl
    .adjustFocus(camIndex, value)
    .then(() => {
      console.log("Focus Adjusted");
      res.send("Focus Adjusted");
    })
    .catch((err) => console.log(err));
});

app.get("/auto", (req, res) => {
  const camIndex = parseInt(req.query.camIndex);
  const value = parseInt(req.query.value);
  camControl
    .setAutoFocus(camIndex, value)
    .then(() => {
      console.log("Auto Focus Updated");
      res.send("Auto Focus Updated");
    })
    .catch((err) => console.log(err));
});

//Making sure Auto Focus is off for both
camControl.webcams.forEach((webcam, i) => {
  camControl.setAutoFocus(i, 0);
});

app.listen(port, () => {
  console.log(`listening at http://localhost:${port}`);
  console.log(ips);
});
