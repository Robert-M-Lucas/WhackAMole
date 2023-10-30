#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Player.h"

void register_output(uint8_t stateOne, uint8_t stateTwo);

pin DATA_PIN = 13;
pin CLOCK_PIN = 11;
pin LATCH_PIN = 12;

pin RANDOM_SEED_PIN = A0;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Shift register indexes for player 1
unsigned int p1Leds[3] = {0, 1, 2};
Player p1(p1Leds, 3, 8);

unsigned int p2Leds[3] = {4, 5, 6};
Player p2(p2Leds, 7, 9);

unsigned int p3Leds[3] = {0, 1, 2};
Player p3(p1Leds, 3, 11);

void setup() {
    Serial.begin(9600);

    lcd.begin(16, 2);
    lcd.print("Starting game...");

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
    delay(1000);
}

void update(unsigned long tick) {
    p1.update(tick);
}

void register_output(uint8_t stateOne, uint8_t stateTwo) {
    // Shift data out to register
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, stateTwo);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, stateOne);

    // Push shift register to actual output
    digitalWrite(LATCH_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
}

void show_leds() {
    // Get register output state as bit flags
    uint8_t registerState = 0b00000000;
    registerState |= p1.getLedBitFlags();

    register_output(registerState, 0);
}

void update_display() {
    Serial.println("Display update");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("P1:");
    lcd.print(p1.getScore());
    lcd.print(" P2:");
    lcd.print(p2.getScore());

    lcd.setCursor(0, 1);
    lcd.print("P3:");
    lcd.print(p3.getScore());
}

// Suitable size, will take 50 days to overflow
unsigned long tick = 0;
unsigned long tick_interval = 10;

void loop() {
    update_display();
    for (int _ = 0; _ < 100; _++) {
        update(tick);
        show_leds();
        delay(tick_interval);
        tick += tick_interval;
    }
}