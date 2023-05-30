#include <OneWire.h>
#include <LoRa.h>

int counter = 0;
int temp_pin = 0;

OneWire ds(temp_pin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = getTemp();
  Serial.print(temp);
  Serial.println(" celsius");
 
  LoRa.beginPacket();
  LoRa.print(temp);
  LoRa.endPacket();
  counter++;
  
  delay(1000);
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
