# AC Current Sensing Meter

This Arduino project measures the RMS value of an AC current using an analog current sensor, displays the result on an LCD, and provides error detection for overcurrent conditions.

It includes:
- An LCD (16x2) display for showing current readings and settings.
- A rotary encoder for adjusting the expected power (watt) value.
- A master button to start and stop the measurement.
- LED indicators for system status and overcurrent alerts.

## 📚 Features
- Set expected watt value using a rotary encoder.
- Measure real-time AC RMS current.
- Display current and watt values on an LCD screen.
- Overcurrent detection with warning message and LED alert.

## 🛠 Hardware Requirements
- Arduino Uno (or compatible board)
- 16x2 LCD (using LiquidCrystal library)
- Current sensor (e.g., ACS712 or similar)
- Rotary encoder with button
- Push button (Master control)
- LEDs for status indication
- Assorted resistors, wires, breadboard

## 📋 Pin Connections
| Component | Arduino Pin |
|:----------|:------------|
| LCD RS    | 10           |
| LCD Enable| 9            |
| LCD D4    | 7            |
| LCD D5    | 6            |
| LCD D6    | 5            |
| LCD D7    | 4            |
| Current Sensor | A3      |
| DC Bias Sensor | A5      |
| Rotary CLK | 2 (Interrupt) |
| Rotary DT | 8           |
| Rotary Button | 11       |
| Master Button | 3 (Interrupt) |
| Status LED | 12 and 13   |

## 🚀 How to Use
1. Upload the code to your Arduino board.
2. Set the expected watt value using the rotary encoder.
3. Press the master button to start measuring.
4. Watch real-time AC current values on the LCD.
5. If overcurrent is detected, an ERROR message appears, and the LED will blink.

## 🧩 Libraries Used
- [LiquidCrystal](https://www.arduino.cc/en/Reference/LiquidCrystal)

## ⚡ Notes
- The calibration factor (`expected_current`) is based on 220V mains voltage. Modify it if your system uses a different voltage.
- You can fine-tune the sensitivity by adjusting the overcurrent threshold in the code.


### Author
> Mohamed Gamil

