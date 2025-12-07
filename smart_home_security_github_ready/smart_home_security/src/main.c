#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "config.h"
#include "lcd.h"
#include "keypad.h"
#include "adc.h"

volatile uint8_t pir_flag = 0;

ISR(INT0_vect){ pir_flag = 1; }

void alarm_on(){
    BUZZER_PORT |= (1<<BUZZER_PIN);
    RELAY_PORT  |= (1<<RELAY1_PIN);
    LED_PORT    |= (1<<LED_RED);
}

void alarm_off(){
    BUZZER_PORT &= ~(1<<BUZZER_PIN);
    RELAY_PORT  &= ~(1<<RELAY1_PIN);
    LED_PORT    &= ~(1<<LED_RED);
}

uint8_t check_password(){
    char pass[PASSWORD_LENGTH];
    uint8_t i=0;
    lcd_clear();
    lcd_print("Enter Password:");
    lcd_goto(1,0);

    while(i < PASSWORD_LENGTH){
        char k = keypad_getkey();
        if(k){
            pass[i] = k;
            lcd_data('*');
            i++;
            _delay_ms(120);
        }
    }

    for(i=0;i<PASSWORD_LENGTH;i++)
        if(pass[i] != correct_password[i])
            return 0;

    return 1;
}

int main(void){
    lcd_init();
    keypad_init();
    adc_init();

    LED_DDR |= (1<<LED_RED)|(1<<LED_GRN)|(1<<LED_BLU);
    RELAY_DDR |= (1<<RELAY1_PIN)|(1<<RELAY2_PIN);
    BUZZER_DDR |= (1<<BUZZER_PIN);

    DDRD &= ~(1<<PIR_PIN);
    PORTD |= (1<<PIR_PIN);
    MCUCR |= (1<<ISC01);
    GICR  |= (1<<INT0);
    sei();

    while(!check_password()){
        lcd_clear();
        lcd_print("Wrong Password");
        _delay_ms(800);
    }

    lcd_clear();
    lcd_print("System Armed");
    LED_PORT |= (1<<LED_GRN);

    while(1){
        uint16_t gas = adc_read(MQ5_ADC_CHANNEL);
        if(gas > MQ5_THRESHOLD || pir_flag){
            pir_flag = 0;
            lcd_clear();
            lcd_print("ALERT !!!");
            alarm_on();
            _delay_ms(2000);
            alarm_off();
            lcd_clear();
            lcd_print("System Armed");
        }
        _delay_ms(150);
    }
}
