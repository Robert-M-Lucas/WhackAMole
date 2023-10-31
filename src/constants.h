//
// Created by rober on 31/10/2023.
//

#ifndef WHACKAMOLE_CONSTANTS_H
#define WHACKAMOLE_CONSTANTS_H

#include "definitions.h"

/// Score needed to win
const int WIN_THRESHOLD = 10;

// Shift register pins
const pin SR_DATA_PIN = 13;
const pin SR_CLOCK_PIN = 11;
const pin SR_LATCH_PIN = 12;

// Source of random seed pin (must be analogue)
const pin RANDOM_SEED_PIN = A0;

/// Initial interval between LED flashes
const unsigned long INITIAL_INTERVAL = 350;

/// Time spent showing next target
const unsigned long SHOW_TARGET_TIME = 3000;
/// Blink interval for new target
const unsigned long TARGET_BLINK_INTERVAL = 500;
/// Time spent with all LED off after showing a target
const unsigned long ALL_LEDS_OFF_PERIOD = 1000;
/// Interval adjustment after a point is won/lost
const unsigned long INTERVAL_DECREMENT_ON_POINT = 5;

#endif //WHACKAMOLE_CONSTANTS_H
