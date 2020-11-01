/*******************************************************************
    Reads input from a Rotary Encoder and sends serial commands
    to control the focus on the webcam

    Should be used with the "serialExample.js" on the PC

    This example using a ESP8266, but could use any Arduino.

    Parts:
    D1 Mini ESP8266 * - http://s.click.aliexpress.com/e/uzFUnIe
    Rotary Encoder * - https://s.click.aliexpress.com/e/_AeDgtJ

    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <Encoder.h>
// Library for using the Rotary Encoder

// Needs to be installed from Github
// The original library by Paul Stoffregen does not work with
// interupts and the ESP8266 anymore, here is a modified version
// https://github.com/RLars/Encoder

// --------
// Rotary Encoder
// --------

const int reButtonPin = D5;
const int reDTPin = D2;
const int reCLKPin = D1;

long oldPosition = -999;
unsigned long reTurnAllowedTime = 0;

int selectedWebCam = 0;

Encoder myEnc(reDTPin, reCLKPin);

void setup()
{
  Serial.begin(115200);

  pinMode(reButtonPin, INPUT_PULLUP); // is pulled HIGH, will be LOW when pressed
  pinMode(D4, OUTPUT);
  digitalWrite(D4, selectedWebCam); //active low

  // put your setup code here, to run once:
  // Get current Position
  oldPosition = myEnc.read();
}

void handleRotaryEncoderTurn()
{
  int amountSecondsChange = 5;

  long newPosition = myEnc.read();

  char command[12];

  if (newPosition > oldPosition)
  {
    //Increase
    sprintf(command, "%s,%d,%d", "adj", selectedWebCam, 5);
  }
  else if (newPosition < oldPosition)
  {
    //Decrease
    sprintf(command, "%s,%d,%d", "adj", selectedWebCam, -5);
  }

  Serial.print(command);

  if (newPosition != oldPosition)
  {
  }

  oldPosition = newPosition;
}

void loop()
{
  if (reTurnAllowedTime < millis())
  {
    handleRotaryEncoderTurn();
    reTurnAllowedTime = millis() + 100;
  }

  if (digitalRead(reButtonPin) == LOW)
  {
    selectedWebCam = !selectedWebCam;
    digitalWrite(D4, selectedWebCam); //active low
    delay(250);
  }
}
