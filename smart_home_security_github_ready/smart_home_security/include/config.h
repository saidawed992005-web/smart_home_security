#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 16000000UL

#define MQ5_ADC_CHANNEL 0
#define MQ5_THRESHOLD 500

#define PIR_PIN PD2

#define BUZZER_PORT PORTC
#define BUZZER_DDR  DDRC
#define BUZZER_PIN  PC5

#define RELAY_PORT PORTC
#define RELAY_DDR  DDRC
#define RELAY1_PIN PC4
#define RELAY2_PIN PC3

#define LED_PORT PORTC
#define LED_DDR  DDRC
#define LED_RED  PC0
#define LED_GRN  PC1
#define LED_BLU  PC2

#define PASSWORD_LENGTH 4
static const char correct_password[PASSWORD_LENGTH] = {'1','2','3','4'};

#endif
