#include <MKRWAN.h>
#include <OneWire.h>

int temp_pin = 0; //

LoRaModem modem;
OneWire ds(temp_pin);


String appEui = "XXX"; // Enter you own appEUI from TTN
String appKey = "XXX"; // Enter your own appKey from TTN


void setup() {
  Serial.begin(115200);
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };


  int connected;
    appKey.trim();
    appEui.trim();

    Serial.println("Connecting...");
    connected = modem.joinOTAA(appEui, appKey);

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {
      Serial.println("Trying again to connect...");
      connected = modem.joinOTAA(appEui, appKey);
      }
  }

  delay(5000);

  int err;
  modem.setPort(3);
  modem.beginPacket();
  modem.print("Connected");
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }


int error;
error = send("connected");
}


void loop() {
      float temp = getTemp();
      while (1){
        int error = send(String(temp));
        if (error > 0) {
          Serial.println("Message sent correctly!");
          break;
        } else {
          Serial.println("Error sending message :(");
        }
      }
      delay(5000);
}

int send(String s) {
  int err;
  modem.setPort(3);
  modem.beginPacket();
  modem.print(s);
  err = modem.endPacket(true);
  return err;
}

float getTemp(){

byte data[12];
byte addr[8];

if ( !ds.search(addr) ) {
  ds.reset_search();
  return -1;
}

if ( OneWire::crc8(addr,7) != addr[7]) {
  Serial.println("crc error");
  return -1;
}

if ( addr[0] != 0x10 && addr[0] != 0x28 ) {
  Serial.println("device error");
  return -1;
}

ds.reset();
ds.select(addr);
ds.write(0x44,1);

byte present = ds.reset();

ds.select(addr);
ds.write(0xBE);

for (int i = 0; i < 9; i++){
  data[i] = ds.read();
}

ds.reset_search();

byte MSB = data[1];
byte LSB = data[0];

float tempread = ((MSB << 8) | LSB);
float tempsum = tempread / 16;

return tempsum;
}
