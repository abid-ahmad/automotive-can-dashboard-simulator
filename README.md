# Automotive CAN Dashboard Simulator

> **Status:** 🚧 **Project in Progress**
> The project is fully functional. I am currently adding final documentation, hardware photos, wiring diagrams, and a demonstration video.

---

## Overview

This project simulates an automotive Controller Area Network (CAN) using two ESP32 microcontrollers, MCP2515 CAN controllers, and an SSD1306 OLED display.

The transmitter ECU generates simulated vehicle data from real-time analog inputs, while the dashboard ECU receives CAN messages, processes the incoming data, and displays vehicle information on an OLED dashboard. The project also includes basic automotive-style diagnostic monitoring and warning detection.

---

## Demo Video

🎥 **Coming Soon**

A complete walkthrough demonstrating:

* Hardware overview
* System architecture
* Live dashboard operation
* CAN communication
* Fault detection
* Project explanation

---

## System Architecture

![System Architecture](diagrams/system_architecture.png)

---

## Wiring Diagram

![Wiring Diagram](diagrams/automotive_can_dashboard_wiring_diagram.png)

---

## Features

* Dual ESP32 architecture
* Real-time CAN communication
* Multiple CAN message IDs
* OLED dashboard display
* Real-time RPM simulation
* Real-time vehicle speed simulation
* Engine temperature monitoring
* Battery voltage monitoring
* Fuel level monitoring
* Potentiometer-based throttle simulation
* Potentiometer-based fuel sensor simulation
* Engine overheat detection (DTC P0217)
* Low fuel warning
* Low battery indication
* CAN communication loss detection

---

## Hardware

| Component               | Quantity |
| ----------------------- | -------: |
| ESP32 Development Board |        2 |
| MCP2515 CAN Controller  |        2 |
| SSD1306 OLED Display    |        1 |
| Potentiometer           |        2 |
| Breadboard              |        2 |
| Jumper Wires            | Multiple |

---

## Software

* Arduino IDE
* Embedded C++
* MCP_CAN Library
* Adafruit GFX Library
* Adafruit SSD1306 Library

---

# How It Works

## Transmitter ECU

The transmitter ESP32 continuously reads two potentiometers.

**Throttle Potentiometer**

Controls:

* Engine RPM (800–6000 RPM)
* Vehicle Speed (0–120 MPH)
* Engine Temperature (70–110 °C)

**Fuel Potentiometer**

Controls:

* Fuel Level (0–100%)

The transmitter packages this information into CAN messages and sends them across the CAN bus.

---

## Dashboard ECU

The dashboard ESP32 receives incoming CAN messages and:

* Decodes the data
* Updates the OLED dashboard
* Checks for warning conditions
* Displays diagnostic information when necessary

---

# CAN Message IDs

| CAN ID    | Data                           |
| --------- | ------------------------------ |
| **0x100** | RPM, Speed, Engine Temperature |
| **0x200** | Battery Voltage, Fuel Level    |

Using multiple CAN IDs better represents how different ECUs communicate on a real automotive CAN network.

---

# Dashboard Display

The OLED dashboard displays:

* Engine RPM
* Vehicle Speed
* Engine Temperature
* Battery Voltage
* Fuel Level

Values update continuously as new CAN messages are received.

---

# Diagnostics

## Engine Overheat

When engine temperature reaches **100 °C or higher**, the dashboard displays:

* ENGINE OVERHEAT
* Diagnostic Trouble Code **P0217**

The warning clears automatically once the temperature returns below the threshold.

---

## Low Fuel

When fuel level drops to **20% or lower**, a Low Fuel warning is displayed.

The warning clears automatically once the fuel level rises above the threshold.

---

## Low Battery

When battery voltage drops to **11.5 V or lower**, the dashboard displays a Low Battery indicator.

---

## CAN Communication Loss

If no CAN messages are received for three seconds, the dashboard displays:

```
NO CAN SIGNAL
```

---

# Project Photos

## Complete System

![Complete System](images/complete_setup.jpg)

---

## Transmitter ECU

![Transmitter ECU](images/transmitter.jpg)

---

## Dashboard ECU

![Dashboard ECU](images/receiver.jpg)

---

## Dashboard Display

![Dashboard Display](images/dashboard.jpg)

---

## Engine Overheat Warning

![Engine Overheat](images/overheat_warning.jpg)

---

## Low Fuel Warning

![Low Fuel Warning](images/low_fuel_warning.jpg)

---

# Repository Structure

```
Automotive-CAN-Dashboard-Simulator
│
├── transmitter_esp32/
│   └── transmitter_esp32.ino
│
├── receiver_dashboard_esp32/
│   └── receiver_dashboard_esp32.ino
│
├── images/
│
├── diagrams/
│   ├── system_architecture.png
│   └── automotive_can_dashboard_wiring_diagram.png
│
├── LICENSE
└── README.md
```

---

# Skills Demonstrated

* Embedded Systems
* Embedded C++
* ESP32 Development
* Controller Area Network (CAN)
* MCP2515 CAN Controller
* SPI Communication
* I²C Communication
* Analog-to-Digital Conversion (ADC)
* Real-Time Embedded Programming
* Automotive Diagnostics
* Hardware Integration
* Embedded Debugging

---

# Future Improvements

Potential future enhancements include:

* Additional ECU nodes
* CAN data logging
* OBD-II integration
* Bluetooth connectivity
* Wi-Fi dashboard
* Mobile application support
* SD card logging
* Real automotive sensors

---

# Author

**Abid Ahmad**

Electrical & Computer Engineering  
Wayne State University

**GitHub:** https://github.com/abid-ahmad

**LinkedIn:** https://www.linkedin.com/in/-abid-ahmad-/
