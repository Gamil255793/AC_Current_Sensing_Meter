#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "lcd.h"

#define current_sensor 3   // ADC3
#define dc_bias_pin 5      // ADC5
#define _NUMBER_OF_SAMPLES 172

volatile signed int samples_raw[_NUMBER_OF_SAMPLES];
volatile signed int dc_bias;
volatile float result;
volatile float average_result;
volatile signed char direction = 0;
volatile uint8_t master_flag = 1;
volatile uint8_t button_previous_state = 0;
volatile uint8_t button_current_state = 0;
signed char watt_num[3] = {0};
char watt_index = 0;
int watt_value = 0;
float expected_current = 0;

void ADC_Init() {
    ADMUX = (1<<REFS0); // AVcc reference
    ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0); // Enable ADC, prescaler 8
}

uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Select ADC channel
    ADCSRA |= (1<<ADSC); // Start conversion
    while (ADCSRA & (1<<ADSC)); // Wait for conversion
    return ADC;
}

void GPIO_Init() {
    DDRD = 0xF0; // PD4-PD7 output for LCD
    DDRC = 0x00; // PC0-PC7 as inputs (ADC pins)
    DDRB |= (1<<PB0); // PB0 as output (LED)
    PORTD |= (1<<PD4); // Pull-up for rotary button
}

void INT_Init() {
    GICR |= (1<<INT0) | (1<<INT1); // Enable INT0, INT1
    MCUCR |= (1<<ISC01) | (1<<ISC11); // Falling edge
    sei(); // Enable global interrupts
}

ISR(INT0_vect) {
    if (PIND & (1<<PD3)) { // Read DT
        direction = 1;
    } else {
        direction = -1;
    }
}

ISR(INT1_vect) {
    master_flag = !master_flag;
    direction = 0;
}

void updateLCD_WattValue() {
    lcd_gotoxy(0,0);
    lcd_print("Watt Value = ");
    lcd_print_int(watt_value);
}

void measure_current() {
    average_result = 0;
    for (uint8_t n = 0; n < 50; n++) {
        dc_bias = ADC_Read(dc_bias_pin);
        result = 0;
        for (uint16_t i = 0; i < _NUMBER_OF_SAMPLES; i++) {
            samples_raw[i] = ADC_Read(current_sensor);
        }
        for (uint16_t i = 0; i < _NUMBER_OF_SAMPLES; i++) {
            samples_raw[i] -= dc_bias;
            if (abs(samples_raw[i]) < 3) samples_raw[i] = 0;
            result += pow(samples_raw[i] * 5.0 / 1023.0, 2);
        }
        result /= _NUMBER_OF_SAMPLES;
        result = sqrt(result);
        result *= 5;
        average_result += result;
    }
    average_result /= 50.0;
}

int main(void) {
    GPIO_Init();
    ADC_Init();
    lcd_init();
    INT_Init();

    lcd_gotoxy(5,0);
    lcd_print("Welcome");
    _delay_ms(1000);
    lcd_clear();
    lcd_gotoxy(3,0);
    lcd_print("AC Current");
    lcd_gotoxy(2,1);
    lcd_print("Sensing Meter");
    _delay_ms(2000);
    lcd_clear();

    button_previous_state = (PIND & (1<<PD4));

    while (1) {
        PORTB &= ~(1<<PB0); // LED off

        if (master_flag) {
            button_current_state = (PIND & (1<<PD4));
            if (button_current_state && !button_previous_state) {
                watt_index++;
                if (watt_index > 2) watt_index = 0;
            }
            button_previous_state = button_current_state;

            if (direction == 1) {
                watt_num[watt_index]++;
                if (watt_num[watt_index] > 9) watt_num[watt_index] = 0;
            } else if (direction == -1) {
                watt_num[watt_index]--;
                if (watt_num[watt_index] < 0) watt_num[watt_index] = 9;
            }
            direction = 0;
            watt_value = 100*watt_num[0] + 10*watt_num[1] + watt_num[2];
            updateLCD_WattValue();
        } else {
            measure_current();
            expected_current = watt_value/220.0;

            if ((average_result - expected_current) > 0.2) {
                lcd_clear();
                lcd_gotoxy(0,0);
                lcd_print("    ERROR     ");
                lcd_gotoxy(0,1);
                lcd_print("HIGH CURRENT!!");
                PORTB |= (1<<PB0); // LED on
            } else {
                lcd_clear();
                lcd_gotoxy(0,0);
                lcd_print("AC I RMS: ");
                lcd_print_float(average_result, 2);
                lcd_gotoxy(0,1);
                lcd_print("Watt Value=");
                lcd_print_int(watt_value);
            }
            _delay_ms(500);
        }
    }
}
