#include <Arduino.h>
#include "constants.h"
#include "led_utils.h"

void flash_leds() {
    Serial.println("Flashing LEDs");
    for (int i = 0; i < 20; i ++) {

        if (i % 2 == 0) {
            // All LEDs on
            register_output(255, 255);
        }
        else {
            // All LEDs off
            register_output(0, 0);
        }
        delay(200);
    }
    register_output(0, 0);
}

void register_output(uint8_t stateOne, uint8_t stateTwo) {
    // Shift data out to register - must be done is reverse (SR2 then SR1 as the first 8 bits are pushed out of SR1 into SR2 by the second byte)
    // MSBFIRST (Most Significant Bit FIRST indicates whether the data should be pushed Left to Right or Right to Left
    shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, stateTwo);
    shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, stateOne);

    // Push shift register to actual output by toggling the latch pin
    digitalWrite(SR_LATCH_PIN, HIGH);
    digitalWrite(SR_LATCH_PIN, LOW);
}