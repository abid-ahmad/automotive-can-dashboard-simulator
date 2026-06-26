# Automotive CAN Dashboard Simulator

> **Status:** 🚧 Under Construction  
> This project is currently in progress and will be updated soon with source code, wiring diagrams, circuit photos, demo videos, and full documentation.

# Automotive CAN Dashboard Simulator

A real-time automotive dashboard simulator built using **dual ESP32 microcontrollers**, **MCP2515 CAN controllers**, and an **SSD1306 OLED display** to emulate vehicle communication over a Controller Area Network (CAN).

This project demonstrates embedded systems programming, CAN bus communication, real-time data processing, analog sensor interfacing, and automotive-style diagnostic monitoring.

---

# Project Demonstration

> **Demo Video**
>
> *(Add your YouTube link here once recorded.)*

---

# Project Overview

Modern vehicles use dozens of Electronic Control Units (ECUs) that continuously exchange information over the CAN bus. This project simulates that architecture using two ESP32 development boards.

The system consists of:

- **Transmitter ECU**
  - Reads analog sensor inputs from potentiometers.
  - Simulates vehicle operating conditions.
  - Packages sensor data into CAN frames.
  - Transmits multiple CAN messages over the CAN bus.

- **Dashboard ECU**
  - Receives CAN frames.
  - Decodes vehicle information.
  - Displays live data on an OLED dashboard.
  - Monitors system faults and displays driver warnings.

The project was designed to resemble a simplified automotive dashboard communication system while remaining easy to understand and expand.

---

# Features

- Dual ESP32 architecture
- Real-time CAN communication
- Multiple CAN message IDs
- OLED dashboard display
- Real-time RPM simulation
- Vehicle speed simulation
- Engine temperature monitoring
- Battery voltage monitoring
- Fuel level simulation
- Potentiometer-based throttle input
- Potentiometer-based fuel sensor input
- Engine Overheat Diagnostic (DTC P0217)
- Low Fuel warning
- Low Battery indicator
- CAN communication loss detection

---

# Hardware Used

| Component | Quantity |
|-----------|---------:|
| ESP32 Development Board | 2 |
| MCP2515 CAN Controller | 2 |
| SSD1306 OLED Display | 1 |
| Potentiometer | 2 |
| Breadboard | 2 |
| Jumper Wires | Multiple |

---

# Software

- Arduino IDE
- Embedded C++
- MCP_CAN Library
- Adafruit GFX Library
- Adafruit SSD1306 Library

---

# System Architecture

```
Throttle Pot ----\
                  \
Fuel Pot ---------> ESP32 (Transmitter ECU)
                         |
                         | SPI
                         ▼
                  MCP2515 CAN Module
                         |
================== CAN BUS ==================
                         |
                  MCP2515 CAN Module
                         ▼
                 ESP32 (Dashboard ECU)
                         |
                         ▼
                    OLED Dashboard
```

*(Replace this diagram later with a professionally drawn image.)*

---

# System Operation

### Transmitter ECU

The transmitter continuously reads two potentiometers.

**Potentiometer 1**

Controls:

- Engine RPM
- Vehicle Speed
- Engine Temperature

**Potentiometer 2**

Controls:

- Fuel Level

The ESP32 converts the analog readings into simulated vehicle values and packages them into CAN messages before transmitting them across the CAN network.

---

### Dashboard ECU

The dashboard ECU listens for incoming CAN frames.

After receiving each message, it:

- Decodes the CAN data
- Updates dashboard values
- Checks for warning conditions
- Displays fault messages when necessary

---

# CAN Message Structure

## CAN ID 0x100 — Engine Data

| Byte | Description |
|------|-------------|
| Byte 0 | Engine RPM |
| Byte 1 | Vehicle Speed |
| Byte 2 | Engine Temperature |

---

## CAN ID 0x200 — Vehicle Status

| Byte | Description |
|------|-------------|
| Byte 0 | Battery Voltage |
| Byte 1 | Fuel Level |

Separating engine and body information into different CAN message IDs more closely reflects how real automotive ECUs communicate.

---

# Dashboard Functions

The OLED dashboard displays:

- Engine RPM
- Vehicle Speed
- Engine Temperature
- Battery Voltage
- Fuel Level

The display updates continuously as new CAN messages arrive.

---

# Diagnostic Features

## Engine Overheat

When engine temperature reaches **100°C**, the dashboard displays:

- ENGINE OVERHEAT
- Diagnostic Trouble Code **P0217**

The warning clears automatically after temperature returns to a safe operating range.

---

## Low Fuel

When fuel level falls below **20%**, the dashboard displays a Low Fuel warning.

The warning automatically clears after fuel rises above the threshold.

---

## Low Battery

Battery voltage is monitored continuously.

If voltage becomes low, the dashboard displays a Low Battery indicator.

---

## CAN Communication Loss

If CAN messages stop arriving, the dashboard displays:

```
NO CAN SIGNAL
```

This simulates communication failure between vehicle ECUs.

---

# Project Photos

## Complete System

![](images/complete_setup.jpg)

---

## Transmitter ECU

![](images/transmitter.jpg)

---

## Dashboard ECU

![](images/receiver.jpg)

---

## Dashboard Display

![](images/dashboard.jpg)

---

## Engine Overheat Warning

![](images/overheat_warning.jpg)

---

## Low Fuel Warning

![](images/low_fuel_warning.jpg)

---

# Repository Structure

```
Automotive-CAN-Dashboard-Simulator
│
├── transmitter_esp32
│   └── transmitter_esp32.ino
│
├── receiver_oled_esp32
│   └── receiver_oled_esp32.ino
│
├── images
│   ├── complete_setup.jpg
│   ├── transmitter.jpg
│   ├── receiver.jpg
│   ├── dashboard.jpg
│   ├── overheat_warning.jpg
│   └── low_fuel_warning.jpg
│
├── diagrams
│   ├── system_architecture.png
│   └── wiring_diagram.png
│
├── LICENSE
│
└── README.md
```

---

# Future Improvements

Possible future enhancements include:

- Additional ECU nodes
- CAN data logging
- SD card storage
- OBD-II compatibility
- Bluetooth monitoring
- Wi-Fi dashboard
- CAN traffic analyzer
- Real automotive sensors

---

# Skills Demonstrated

This project demonstrates experience with:

- Embedded Systems
- Embedded C++
- ESP32 Development
- CAN Bus Communication
- MCP2515 CAN Controller
- SPI Communication
- I2C Communication
- OLED Displays
- Analog-to-Digital Conversion (ADC)
- Real-Time Embedded Programming
- Automotive Diagnostics
- Sensor Simulation
- Hardware Integration
- Debugging and Testing

---

# Author

**Abid Ahmad**

Electrical & Computer Engineering  
Wayne State University

GitHub: *([Add your GitHub profile link here](https://github.com/abid-ahmad).)*

LinkedIn: *(LinkedIn: *(inkedin.com/in/-abid-ahmad-)*.)*
