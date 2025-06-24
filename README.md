# Arduino-UNO Air-Quality Monitor  
Measures temperature, humidity, smoke (MQ-2) and multi-gas levels (MQ-135) and streams live data to the Arduino IDE Serial Monitor.

## Features
- DHT11 sensor for ambient temperature & humidity.  
- MQ-2 for smoke/LPG concentration.  
- MQ-135 for CO₂, NH₃, benzene and other gases[2].  
- All readings printed to the built-in Serial Monitor.
- Modular sketch with simple calibration helpers.

## Bill of Materials
| Qty | Component | Notes |
| --- | --------- | ----- |
| 1 | Arduino UNO (5 V) | ‑ |
| 1 | DHT11 | Temp + RH |
| 1 | MQ-2 gas sensor | Smoke/LPG |
| 1 | MQ-135 gas sensor | Multi-gas |
| – | Breadboard & jumper wires | prototyping |

## Wiring
| Sensor pin | Arduino pin |
| ---------- | ----------- |
| DHT11 DATA | D2 |
| MQ-2 AOUT  | A1 |
| MQ-135 AOUT| A0 |
| VCC / GND  | 5 V / GND (all sensors) |


