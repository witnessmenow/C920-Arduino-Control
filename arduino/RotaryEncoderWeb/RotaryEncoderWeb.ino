// ----------------------------
// Standard Libraries
// ----------------------------

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// ----------------------------
// Additional Libraries - will need to be installed
// ----------------------------

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

// ---------
// Wifi
// ----------

//------- Replace the following! ------
char ssid[] = "SSID";       // your network SSID (name)
char password[] = "password";  // your network key

WiFiClient client;

// Ip Address of computer
IPAddress server(192, 168, 1, 32);
#define SERVER_PORT 3000

int selectedWebCam = 0;

Encoder myEnc(reDTPin, reCLKPin);

void setup() {
  Serial.begin(115200);

  pinMode(reButtonPin, INPUT_PULLUP); // is pulled HIGH, will be LOW when pressed
  pinMode(D4, OUTPUT);
  digitalWrite(D4, selectedWebCam); //active low

  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  // put your setup code here, to run once:
  // Get current Position
  oldPosition = myEnc.read();
}

void handleRotaryEncoderTurn() {
  int amountSecondsChange = 5;

  long newPosition = myEnc.read();

  char command[30];

  if (newPosition > oldPosition) {
    //Increase
    sprintf(command, "/%s?camIndex=%d&value=%d", "adj", selectedWebCam, 5);
  } else if (newPosition < oldPosition) {
    //Decrease
    sprintf(command, "/%s?camIndex=%d&value=%d", "adj", selectedWebCam, -5);
  }

  if (newPosition != oldPosition) {
    Serial.print(command);
    char message[50];
    sprintf(message, "GET %s HTTP/1.0", command);

    if (client.connect(server, SERVER_PORT)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println(message);
      client.println();
    }
  }

  oldPosition = newPosition;
}

void loop() {
  if (reTurnAllowedTime < millis()) {
    handleRotaryEncoderTurn();
    reTurnAllowedTime = millis() + 200;
  }

  if (digitalRead(reButtonPin) == LOW)
  {
    selectedWebCam = !selectedWebCam;
    digitalWrite(D4, selectedWebCam); //active low
    delay(250);
  }

}
