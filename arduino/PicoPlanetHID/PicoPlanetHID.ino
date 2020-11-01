/*******************************************************************
    Uses a Bleeptrack's PicoPlanet to send macro keyboard commands
    for controlling the focus on the webcam

    Should be used with the "keyboardListenerExample.js" on the PC

    The example is based on BleepTrack's Audiokeyboard example for the PicoPlanet
    https://github.com/bleeptrack/picoplanet/blob/master/example/arduino/Audiokeyboard.ino

    Parts:
    PicoPlanet - https://www.tindie.com/products/bleeptrack/picoplanet/

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

#include "Adafruit_FreeTouch.h"
// For reading the capacitive touch buttons

// Search for "Freetouch" in the Arduino Library Manager.
// https://github.com/adafruit/Adafruit_FreeTouch

#include "HID-Project.h"
// For sending the HID commands.

// Search for "HID-project" in the Arduino Library Manager
// Install the one by NicoHood
// https://github.com/NicoHood/HID

#include "Adafruit_FreeTouch.h"
#include "HID-Project.h" //uncomment if HID library installed. See top comment

//capacitive button init
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(A0, OVERSAMPLE_4, RESISTOR_20K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(A1, OVERSAMPLE_4, RESISTOR_20K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_3 = Adafruit_FreeTouch(A2, OVERSAMPLE_4, RESISTOR_20K, FREQ_MODE_NONE);

void setup()
{

  Serial.begin(9600);

  //Set LED lines as output so we can use them
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  //check if capacitive buttons are working
  if (!qt_1.begin())
    Serial.println("Failed to begin qt on pin A0");
  if (!qt_2.begin())
    Serial.println("Failed to begin qt on pin A0");
  if (!qt_3.begin())
    Serial.println("Failed to begin qt on pin A0");

  Keyboard.begin(); //uncomment if HID library installed. See top comment
  Consumer.begin();
}

// This will hold down all the following buttons.
void sendMacroCommand(KeyboardKeycode key)
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(key);
}

void loop()
{

  //meassure values at capacitive touch buttons
  int result1 = qt_1.measure();
  int result2 = qt_2.measure();
  int result3 = qt_3.measure();

  //check if button is pressed aka value is high enough
  //important: LEDs are active when LOW!
  if (result1 > 500)
  {
    digitalWrite(LED_R, LOW);
    sendMacroCommand(KEY_DOWN_ARROW);
    delay(200);
    Keyboard.releaseAll();
  }
  else
  {
    digitalWrite(LED_R, HIGH);
  }

  if (result2 > 500)
  {
    digitalWrite(LED_G, LOW);
    sendMacroCommand(KEY_SPACE);
    delay(200);
    Keyboard.releaseAll();
  }
  else
  {
    digitalWrite(LED_G, HIGH);
  }

  if (result3 > 500)
  {
    digitalWrite(LED_B, LOW);
    sendMacroCommand(KEY_UP_ARROW);
    delay(200);
    Keyboard.releaseAll();
  }
  else
  {
    digitalWrite(LED_B, HIGH);
  }
}
