AC Current Sensing Meter — AVR ATmega32
This project implements an AC Current Sensing Meter using an ATmega32 microcontroller, a current sensor, a 16x2 LCD, and a rotary encoder for user input.

The project measures AC RMS current based on ADC readings, compares it to a user-configured "expected" value (in watts), and warns if the current exceeds the limit.

📦 Project Features
📟 16x2 LCD Display (4-bit mode) for showing:

Watt target

Measured RMS current

🎛 Rotary Encoder to set Watt Value easily

🔘 Master Button to start measurement

⚡ LED Warning when current exceeds expected value

🧠 Pure AVR C Code (no Arduino libraries)

🎯 Interrupts for responsive rotary encoder and button handling

🔬 Accurate ADC sampling and RMS calculation over multiple cycles

🛠 Hardware Connections

Peripheral	ATmega32 Pin	Notes
LCD RS	PD4	
LCD Enable (E)	PD5	
LCD D4	PD6	
LCD D5	PD7	
LCD D6	PC0	Modify if needed
LCD D7	PC1	Modify if needed
Rotary Encoder CLK	INT0 (PD2)	External Interrupt 0
Rotary Encoder DT	PD3	Read manually
Rotary Encoder Button	PD4	Pulled high internally
Master Button	INT1 (PD3)	External Interrupt 1
Current Sensor	ADC3 (PC3)	Analog Read Input
DC Bias Input	ADC5 (PC5)	Reference voltage
LED Indicator	PB0	High Current Alarm
📋 Requirements
ATmega32 Microcontroller

16x2 LCD (HD44780 compatible)

Rotary Encoder (with push button)

ACS712 / SCT-013 or similar current sensor

220V AC Load (lamp, heater, etc.)

External 5V Power Supply

USBASP or AVR Programmer

avr-gcc / avrdude (for flashing)

🧰 How It Works
Power on: LCD displays welcome screen.

Set Expected Watt Value using rotary encoder:

Rotate to change digits.

Press encoder button to move between digits.

Press Master Button to start measurement.

Current is sampled and true RMS is calculated.

If measured current exceeds the expected current:

"ERROR: HIGH CURRENT" appears.

LED warning light turns ON.

Otherwise, displays real-time RMS current value.

🚀 Building & Flashing
bash
Copy
Edit
make clean
make all
make flash
Make sure your Makefile is properly set with your programmer (e.g., USBASP).

Use avrdude to upload .hex to the ATmega32.

🗂 Project Structure
bash
Copy
Edit
/ac-current-sensor-avr/
│
├── main.c        # Main Application Logic
├── lcd.c         # LCD control functions
├── lcd.h         # LCD header
├── Makefile      # Build file
└── README.md     # Project description
⚡ Screenshots
(Optional: insert pictures later if you want to show the LCD in operation.)

✍️ Author
Written by: Mohamed Gamil

📢 Important Notes
Make sure to use proper isolation when sensing high AC voltage.

Always be cautious while handling AC mains!
