# Automotive CAN Dashboard Simulator

> **Status:** 🚧 Under Construction  
> This project is currently in progress and will be updated soon with source code, wiring diagrams, circuit photos, demo videos, and full documentation.

## Overview

The **Automotive CAN Dashboard Simulator** is an embedded systems project designed to emulate real-time vehicle communication using a CAN bus network. The system uses dual ESP32 microcontrollers, MCP2515 CAN controllers, and an OLED display to simulate vehicle dashboard data and diagnostic warning behavior.

This project demonstrates how automotive-style sensor data can be transmitted, received, decoded, and displayed using CAN message IDs.

## Features

- Dual ESP32-based CAN communication setup
- MCP2515 CAN controller integration
- OLED dashboard display for real-time vehicle data
- Potentiometer-based sensor simulation for throttle and fuel inputs
- Real-time display of:
  - RPM
  - Speed
  - Engine temperature
  - Battery voltage
  - Fuel level
- Multiple CAN message IDs for simulated vehicle signals
- Diagnostic and warning features, including:
  - DTC P0217 Engine Overheat
  - Low-fuel warning
  - Low-battery indication
  - CAN communication-loss detection

## Hardware Used

- 2x ESP32 development boards
- 2x MCP2515 CAN bus modules
- OLED display
- Potentiometers
- Jumper wires
- Breadboard
- Power supply / USB power
- Resistors as needed

## Project Goals

The goal of this project is to build a small-scale automotive CAN network simulator that demonstrates embedded communication, sensor simulation, dashboard visualization, and diagnostic logic.

This project is intended to show practical experience with:

- Embedded systems
- CAN bus communication
- ESP32 development
- Automotive diagnostics
- Sensor simulation
- Real-time data display
- Hardware debugging

## Planned Updates

The following items will be added soon:

- Source code for transmitter and receiver ESP32 boards
- CAN message ID table
- Wiring diagram
- Circuit photos
- OLED display screenshots
- Demo video
- Setup instructions
- Troubleshooting notes
- Final project results

## Repository Status

This repository is currently a work in progress. More files and documentation will be added as the project is completed.

## Author

**Abid Ahmad**  
Electrical and Computer Engineering  
Wayne State University
