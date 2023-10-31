//
// Created by rober on 31/10/2023.
//

#include <Arduino.h>
#include "constants.h"
#include "led_utils.h"

void flash_leds() {
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
    // Shift data out to register
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, stateTwo);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, stateOne);

    // Push shift register to actual output
    digitalWrite(LATCH_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
}