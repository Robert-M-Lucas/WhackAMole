#include <Arduino.h>
#include "Player.h"

void register_output(uint8_t state);

pin DATA_PIN = 4;
pin CLOCK_PIN = 6;
pin LATCH_PIN = 5;

pin RANDOM_SEED_PIN = A0;

// Shift register indexes for player 1
unsigned int p1Leds[3] = {0, 1, 2};
Player p1(p1Leds, 3, 2);

void setup() {
    Serial.begin(9600);

    pinMode(RANDOM_SEED_PIN, INPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);

    // Set analogue noise as our random seed to ensure unique games
    randomSeed(analogRead(RANDOM_SEED_PIN));

    // Target must be randomised AFTER random seed is set
    p1.randomiseTarget();

    // Pre-game delay
    // Clear register
    for (int _ = 0; _ < 40; _ ++) {
        register_output(random(256));
        delay(100);
    }
    register_output(0);
    delay(1000);
}

void update(unsigned long tick) {
    p1.update(tick);
}

void register_output(uint8_t state) {
    // Shift data out to register
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, state);

    // Push shift register to actual output
    digitalWrite(LATCH_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
}

void display() {
    // Get register output state as bit flags
    uint8_t registerState = 0b00000000;
    registerState |= p1.getLedBitFlags();

    register_output(registerState);
}

unsigned long tick = 0;
unsigned long tick_interval = 10;

void loop() {
    update(tick);
    display();

    delay(tick_interval);
    tick += tick_interval;
}