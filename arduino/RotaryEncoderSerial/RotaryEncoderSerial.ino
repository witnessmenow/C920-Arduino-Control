#include <Encoder.h>
// Library for using the Rotary Encoder
// The original library by Paul Stoffregen does not work with
// interupts and the ESP8266 anymore, here is a modified version
// https://github.com/RLars/Encoder

// --------
// Rotary Encoder
// --------

const int reButtonPin = D5;
const int reDTPin = D2;
const int reCLKPin = D1;

long oldPosition  = -999;
unsigned long reTurnAllowedTime = 0;

int selectedWebCam = 0;

Encoder myEnc(reDTPin, reCLKPin);

void setup() {
  Serial.begin(115200);

  pinMode(reButtonPin, INPUT_PULLUP); // is pulled HIGH, will be LOW when pressed
  pinMode(D4, OUTPUT);
  digitalWrite(D4, selectedWebCam); //active low
  
  // put your setup code here, to run once:
    // Get current Position
  oldPosition = myEnc.read();
}

void handleRotaryEncoderTurn() {
  int amountSecondsChange = 5;

  long newPosition = myEnc.read();

  char command[12];
  
  if (newPosition > oldPosition) {
    //Increase
    sprintf(command, "%s,%d,%d", "adj", selectedWebCam, 5);
  } else if (newPosition < oldPosition) {
    //Decrease
    sprintf(command, "%s,%d,%d", "adj", selectedWebCam, -5);
  }

  Serial.print(command);

  if (newPosition != oldPosition) {
  }

  oldPosition = newPosition;
}

void loop() {
    if (reTurnAllowedTime < millis()) {
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
