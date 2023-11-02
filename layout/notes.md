# Layout

## Arduino Pins
- Pins 2 - 7 are used to control the LCD
- Pins 8, 9 and 10 are used to read the button states for players 3, 2 and 1 respectively
- Pin 11 is used for the Piezo buzzer which requires a PWM (~) pin
- Pins 12, 13 and A4 are used as the latch, data and clock pin for the shift register respectively
(with A4 functioning in digital mode)
- Pin A3 is used to read the value of the potentiometer for setting the game's difficulty
- Pin A5 is used for controlling the servo (functioning in digital mode)
- Pin A0 is used to seed the random number generator by reading random noise. It must not be connected to anything

### Notes

- Some analogue pins were used as digital pins due to a lack of available digital pins

## Shift Registers

### Pins

Pin-out diagram can be found here: https://www.ti.com/lit/ds/symlink/sn74hc595.pdf
- VCC - Power
- GND - Ground
- SER - (Serial) Input
- SRCLK - Clock
- RCLK - Latch
- SRCLR - Clear
- OE - Output Enable
- Q(A) - Q(H) - Output pins 1 - 8
- Q(H\') - Mirrors output Q(H). Used as the input for the second register for daisy-chaining

### Notes

The 2 shift register used are daisy-chained. This is done by connecting the output of the last bit of the first register
to the input of the second and by tying the clock and latch signal together for both of them. By pushing 16 bits to the 
first register instead of 8, the first 8 bits will be pushed to the second register and the first 8 will be pushed to
the first register.

The shift register clear pin on both registers is tied to high as it is active low as we never want to clear
the registers, instead pushing the old data out with the new data.

The output enable pin on both registers is tied to low as it is active low as we want the output to always be enabled.

## LEDs

The LEDs are powered by the shift registers and are connected to ground by 220 Ohm resistors

## Buttons

The buttons each have a 10 kOhm pull-down resistor to ensure the pins read LOW until the button is pressed.

## Piezo

The Piezo buzzer is connected to a PWM pin which is required for producing various tones.

## LCD

The LCD uses a 220 Ohm resistor (instead of a potentiometer which seems to be more common in most guides) to set the
contrast of the display.