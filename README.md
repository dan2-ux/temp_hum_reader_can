# This respositoty is about reading sensor signals using can.

## Hardware Required

- 2 × Arduino Uno R4 WiFi

- 2 × MCP2515 CAN Bus modules (TJA1050 transceiver)

- Jumper wires & breadboard

- 1 × LED + resistor (for control demo)

- 1 × Sensor (DHT11, potentiometer, or any simple analog sensor)

- Termination resistors (120 Ω) if needed

## Wiring (for each Arduino + MCP2515)

|              Arduino Uno R4                  |              MCP2515                |
|----------------------------------------------|-------------------------------------|
|                   VCC                        |                 5V                  |
|                   GND                        |                 GND                 |
|                   CS                         |                 pin 10              |
|                   SO                         |                 pin 12              |
|                   SI                         |                 pin 11              |
|                   SCK                        |                 pin 13              |
|                   INT                        |                 pin 2               |


|                Can Bus FD                    |               Can Bus FD            |
|----------------------------------------------|-------------------------------------| 
|                  can0_H                      |                can1_H               |
|                  can0_L                      |                can1_L               |

|                Arduino Uno R4                |                 DHT11               |
|----------------------------------------------|-------------------------------------| 
|                   5V                         |                  VCC                |
|                  pin 3                       |                DATA pin             |
|                   GND                        |                  GND                |

# Software Requirements
Use the *mcp_can*

## Workflow
Both arduino is communicating through Can prototype, on the sensor arudio which is connected to dht11 to contuesouly read and send signal back to controller arduino which is connected to a led. If temperature surpass 40 degree and humidity is greater then 70% which will make the led on control arduino shine.


