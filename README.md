#  Industrial IoT / Industry 4.0 demonstrator

The project demonstrates modular industrial nodes (sensor, actuator, transport and machine nodes) communicating in a decentralized architecture inspired by Industry 4.0 concepts.
This project was originally developed in 2018/2019 as part of a Master's research project at the FH Vorarlberg.
The focus was on demonstrating modular Industry 4.0 concepts using low-cost embedded hardware and OPC UA communication.

In this project a OPC UA distribution from https://open65421.org and wiringPi library from
http://wiringpi.com was used.

See original Dokumentation for further details.

## Build Requirements

- Raspberry Pi OS
- GCC
- open62541
- wiringPi

## Repository Structure

- `/sensorNode`
  OPC UA sensor node implementation

- `/actuatorNode`
  Actuator and maintenance node

- `/machineNode`
  Simulated machine controller

- `/transportNode`
  RFID-based transport node

- `/hwTest`
  Hardware interface and GPIO test programs

- `/master`
  Startup and node configuration handling

- `/docs`
  Documentation, diagrams and thesis excerpts
  
## Lessons Learned / Modern Perspective

Today the system would likely use:

- containerized edge services
- MQTT/UNS architectures
- industrial edge hardware
- improved security concepts
- OPC UA PubSub
- cloud-edge integration
