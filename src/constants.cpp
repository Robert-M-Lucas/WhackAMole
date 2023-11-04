//
// Created by rober on 04/11/2023.
//
#include "constants.h"
#include <Arduino.h>

void print_config() {
    Serial.println("Config:");
    Serial.print("\tPoints to win: "); Serial.println(WIN_THRESHOLD);
    Serial.print("\tDifficulty increment on point scored: "); Serial.println(INTERVAL_DECREMENT_ON_POINT);
    Serial.print("\tMin start difficulty: "); Serial.println(MINIMUM_DIFFICULTY);
    Serial.print("\tMax start difficulty: "); Serial.println(MAXIMUM_DIFFICULTY);
    Serial.print("\tMin game difficulty: "); Serial.println(MINIMUM_GAMEPLAY_DIFFICULTY);
    Serial.print("\tMin game difficulty: "); Serial.println(MINIMUM_GAMEPLAY_DIFFICULTY);
    Serial.print("\tTime to pick difficulty: "); Serial.println(DIFFICULTY_PICK_TIME_MS);
    Serial.print("\tTarget show time: "); Serial.println(SHOW_TARGET_TIME);
    Serial.print("\tTarget blink interval: "); Serial.println(TARGET_BLINK_INTERVAL);
    Serial.print("\tLEDs off time: "); Serial.println(ALL_LEDS_OFF_PERIOD);
}

