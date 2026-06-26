// include the spi library because the esp32 talks to the mcp2515 using spi
#include <SPI.h>

// include the mcp_can library so we can send can messages
#include <mcp_can.h>

// pin connections
// this is the chip select pin for the mcp2515 can module
#define CAN_CS 5

// this potentiometer acts like the throttle input
#define THROTTLE_PIN 34

// this potentiometer acts like the fuel level input 
#define FUEL_PIN 35

// create the can object and tell it which cs pin to use
MCP_CAN CAN(CAN_CS);

// battery value is stored as 126 = 12.6v
int battery = 126;

void setup() {
  // start serial monitor so we can see messages while testing
  Serial.begin(115200);

  // small delay so the board has time to start
  delay(1000);

  Serial.println("Transmitter Starting...");

  // start the mcp2515 can module
  // 500kbps is the can speed, and 8mhz is the crystal speed on the module
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN Module Ready");
  } else {
    Serial.println("CAN Module Failed");

    // stop here if the can module does not start
    while (1);
  }

  // put the can module into normal mode so it can actually send messages
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  // read potentiometers
  // throttlevalue goes from about 0 to 4095 on the esp32
  int throttleValue = analogRead(THROTTLE_PIN);

  // fuelvalue also goes from about 0 to 4095
  int fuelValue = analogRead(FUEL_PIN);

  // convert potentiometer values to vehicle values
  // throttle controls rpm
  int rpm = map(throttleValue, 0, 4095, 800, 6000);

  // throttle also controls speed
  int speed = map(throttleValue, 0, 4095, 0, 120);

  // throttle also controls engine temperature for the simulation
  int temperature = map(throttleValue, 0, 4095, 70, 110);

  // fuel potentiometer controls fuel percentage
  int fuel = map(fuelValue, 0, 4095, 0, 100);

  // simulated battery voltage
  // this slowly decreases the battery value for demo purposes
  battery--;

  // when battery gets too low, reset it back to 12.6v
  if (battery < 110) {
    battery = 126;
  }

  // can id 0x100 = engine data
  // this message carries rpm, speed, and temperature
  byte engineData[3];

  // rpm is divided by 100 so it can fit inside one byte
  engineData[0] = rpm / 100;

  // speed is already small enough to fit in one byte
  engineData[1] = speed;

  // temperature is also small enough to fit in one byte
  engineData[2] = temperature;

  // can id 0x200 = body data
  // this message carries battery and fuel information
  byte bodyData[2];

  // battery is stored as 126 for 12.6v, 115 for 11.5v, etc.
  bodyData[0] = battery;

  // fuel is stored as a percentage from 0 to 100
  bodyData[1] = fuel;

  // send engine data using can id 0x100
  CAN.sendMsgBuf(0x100, 0, 3, engineData);

  // small delay between messages so the bus is not spammed too fast
  delay(10);

  // send battery and fuel data using can id 0x200
  CAN.sendMsgBuf(0x200, 0, 2, bodyData);

  // update about 5 times per second
  delay(200);
}
