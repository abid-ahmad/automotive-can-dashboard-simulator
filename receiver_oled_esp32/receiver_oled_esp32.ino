// include spi because the esp32 talks to the mcp2515 can module using spi
#include <SPI.h>

// include the can library for the mcp2515 module
#include <mcp_can.h>

// include wire because the oled uses i2c communication
#include <Wire.h>

// include graphics library for drawing text on the oled
#include <Adafruit_GFX.h>

// include oled display library
#include <Adafruit_SSD1306.h>

// can pins
// cs is the chip select pin for the mcp2515
#define CAN_CS 5

// int pin tells the esp32 when a can message has arrived
#define CAN_INT 4

// oled settings
// this oled is 128 pixels wide and 64 pixels tall
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// reset pin is not used for this oled module
#define OLED_RESET -1

// create the can object
MCP_CAN CAN(CAN_CS);

// create the oled display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// vehicle values that will be shown on the dashboard
int rpm = 0;
int speed = 0;
int temperature = 0;
float battery = 0.0;
int fuel = 0;

// used for no can signal warning
// this stores the last time a can message was received
unsigned long lastMessageTime = 0;

// used so warning popups do not repeat forever
bool overheatWarningShown = false;
bool lowFuelWarningShown = false;

void setup() {
  // start serial monitor for testing and debugging
  Serial.begin(115200);
  delay(1000);

  // set the can interrupt pin as an input
  pinMode(CAN_INT, INPUT);

  // start the oled display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");

    // stop here if the oled does not start
    while (1);
  }

  // show the startup screen first
  showStartupScreen();

  // start the mcp2515 can module
  // 500kbps is the can speed, and 8mhz is the crystal on the module
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN Module Ready");
  } else {
    Serial.println("CAN Module Failed");

    // stop here if can does not start
    while (1);
  }

  // put the can module in normal mode so it can receive messages
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  // if the interrupt pin is low, a can message is available
  if (digitalRead(CAN_INT) == LOW) {
    // read the incoming can message
    readCanMessage();

    // check if any warning should be shown
    checkWarnings();

    // update the oled dashboard
    showDashboard();
  }

  // if no can message arrives for 3 seconds, show no signal warning
  if (millis() - lastMessageTime > 3000) {
    showNoSignalScreen();
  }
}

void readCanMessage() {
  // this stores the can message id
  long unsigned int messageID;

  // this stores how many data bytes are received
  unsigned char length = 0;

  // this array stores the actual can data bytes
  unsigned char data[8];

  // read the can message from the mcp2515
  CAN.readMsgBuf(&messageID, &length, data);

  // update the last message time because a message was received
  lastMessageTime = millis();

  // can id 0x100 = engine data
  // this message contains rpm, speed, and temperature
  if (messageID == 0x100) {
    rpm = data[0] * 100;
    speed = data[1];
    temperature = data[2];
  }

  // can id 0x200 = battery and fuel data
  // this message contains battery voltage and fuel level
  if (messageID == 0x200) {
    battery = data[0] / 10.0;
    fuel = data[1];
  }
}

void checkWarnings() {
  // show dtc p0217 only once when engine first overheats
  if (temperature >= 100 && overheatWarningShown == false) {
    showOverheatWarning();
    overheatWarningShown = true;
  }

  // reset overheat warning when temperature goes back to normal
  if (temperature < 100) {
    overheatWarningShown = false;
  }

  // show low fuel warning only once
  if (fuel <= 20 && lowFuelWarningShown == false) {
    showLowFuelWarning();
    lowFuelWarningShown = true;
  }

  // reset low fuel warning when fuel goes above 20%
  if (fuel > 20) {
    lowFuelWarningShown = false;
  }
}

void showStartupScreen() {
  // clear anything already on the oled
  display.clearDisplay();

  // use small text
  display.setTextSize(1);

  // use white text
  display.setTextColor(SSD1306_WHITE);

  // print startup title
  display.setCursor(0, 0);
  display.println("AUTOMOTIVE CAN");
  display.println("DASHBOARD");
  display.println();
  display.println("Starting...");

  // send the text to the oled
  display.display();

  // keep startup screen visible for 2 seconds
  delay(2000);
}

void showDashboard() {
  // clear the oled before drawing new values
  display.clearDisplay();
  display.setTextSize(1);

  // dashboard title
  display.setCursor(0, 0);
  display.println("AUTO CAN DASH");

  // show rpm
  display.setCursor(0, 11);
  display.print("RPM: ");
  display.println(rpm);

  // show speed
  display.setCursor(0, 22);
  display.print("SPD: ");
  display.print(speed);
  display.println(" MPH");

  // show engine temperature
  display.setCursor(0, 33);
  display.print("TMP: ");
  display.print(temperature);
  display.println(" C");

  // show battery voltage
  display.setCursor(0, 44);
  display.print("BAT: ");
  display.print(battery);
  display.println(" V");

  // show fuel percentage
  display.setCursor(0, 55);
  display.print("FUEL: ");
  display.print(fuel);
  display.println("%");

  // small label if temperature is high
  if (temperature >= 100) {
    display.setCursor(90, 33);
    display.print("HOT");
  }

  // small label if battery is low
  if (battery <= 11.5 && battery > 0) {
    display.setCursor(90, 44);
    display.print("LOW");
  }

  // small label if fuel is low
  if (fuel <= 20) {
    display.setCursor(90, 55);
    display.print("LOW");
  }

  // update the oled with everything we just drew
  display.display();
}

void showOverheatWarning() {
  // clear the normal dashboard screen
  display.clearDisplay();
  display.setTextSize(1);

  // warning title
  display.setCursor(10, 0);
  display.println("!!! WARNING !!!");

  // warning message
  display.setCursor(5, 18);
  display.println("ENGINE OVERHEAT");

  // diagnostic trouble code for engine overheat
  display.setCursor(25, 35);
  display.println("DTC: P0217");

  // show the temperature that caused the warning
  display.setCursor(10, 52);
  display.print("TEMP: ");
  display.print(temperature);
  display.println(" C");

  // send warning to oled
  display.display();

  // keep warning visible for a short time
  delay(1200);
}

void showLowFuelWarning() {
  // clear the normal dashboard screen
  display.clearDisplay();
  display.setTextSize(1);

  // warning title
  display.setCursor(10, 0);
  display.println("!!! WARNING !!!");

  // low fuel message
  display.setCursor(25, 22);
  display.println("LOW FUEL");

  // show current fuel level
  display.setCursor(20, 42);
  display.print("FUEL: ");
  display.print(fuel);
  display.println("%");

  // send warning to oled
  display.display();

  // keep warning visible for a short time
  delay(1200);
}

void showNoSignalScreen() {
  // clear the display
  display.clearDisplay();
  display.setTextSize(1);

  // show communication loss warning
  display.setCursor(0, 0);
  display.println("AUTOMOTIVE CAN");
  display.println("DASHBOARD");
  display.println();
  display.println("NO CAN SIGNAL");

  // update oled
  display.display();
}