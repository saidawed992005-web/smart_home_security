MCU = atmega32
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy

CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
SRC = src/main.c src/lcd.c src/keypad.c src/adc.c
OBJ = $(SRC:.c=.o)
TARGET = smart_home_security

all: $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f src/*.o *.elf *.hex
