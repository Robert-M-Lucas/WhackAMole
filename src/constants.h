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
const pin SR_CLOCK_PIN = A4;
const pin SR_LATCH_PIN = 12;

const pin PIEZO_PIN = 11;

const pin DIFFICULTY_PIN = A3;

const unsigned long MINIMUM_DIFFICULTY = 200;
const unsigned long MAXIMUM_DIFFICULTY = 500;
const unsigned long MINIMUM_GAMEPLAY_DIFFICULTY = 180;
const unsigned long MAXIMUM_GAMEPLAY_DIFFICULTY = 600;
const unsigned long DIFFICULTY_PICK_TIME_MS = 10000;

// Source of random seed pin (must be analogue)
const pin RANDOM_SEED_PIN = A0;

/// Time spent showing next target
const unsigned long SHOW_TARGET_TIME = 3000;
/// Blink interval for new target
const unsigned long TARGET_BLINK_INTERVAL = 500;
/// Time spent with all LED off after showing a target
const unsigned long ALL_LEDS_OFF_PERIOD = 1000;
/// Interval adjustment after a point is won/lost
const unsigned long INTERVAL_DECREMENT_ON_POINT = 5;

#endif //WHACKAMOLE_CONSTANTS_H
