/*
  First Configuration
  This sketch demonstrates the usage of MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>

LoRaModem modem;

// Uncomment if using the Murata chip as a module
// LoRaModem modem(Serial1);

String appEui = "XXX"; //Enter your own appEUI and appKey values here
String appKey = "XXX";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  int connected;
  appKey.trim();
  appEui.trim();

  Serial.println("Connecting...");
  connected = modem.joinOTAA(appEui, appKey);

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {
      Serial.println("Connecting...");
      connected = modem.joinOTAA(appEui, appKey);}
  }

  delay(5000);

  int err;
  modem.setPort(3);
  modem.beginPacket();
  modem.print("HeLoRA world!");
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }
}

void loop() {
      float temp = 25.05; 
      modem.setPort(3);
      modem.beginPacket();
      modem.print(String(temp));
      modem.endPacket(true);
      delay(5000);
      temp = 25.87;
      modem.setPort(3);
      modem.beginPacket();
      modem.print(String(temp));
      modem.endPacket(true);
      delay(5000);
      temp = 26.17;
      modem.setPort(3);
      modem.beginPacket();
      modem.print(String(temp));
      modem.endPacket(true);
      delay(5000);
}
