//
// Created by rober on 31/10/2023.
//

#include <Arduino.h>
#include "constants.h"
#include "led_utils.h"

void flash_leds() {
    Serial.println("Flashing LEDs");
    for (int i = 0; i < 20; i ++) {
        if (i % 2 == 0) {
            register_output(255, 255);
        }
        else {
            register_output(0, 0);
        }
        delay(200);
    }
    register_output(0, 0);
}

void register_output(uint8_t stateOne, uint8_t stateTwo) {
    // Shift data out to register - must be done is reverse (SR2 then SR1 as the first 8 bits are pushed out of SR1 into SR2 by the second byte)
    shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, stateTwo);
    shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, stateOne);

    // Push shift register to actual output
    digitalWrite(SR_LATCH_PIN, HIGH);
    digitalWrite(SR_LATCH_PIN, LOW);
}