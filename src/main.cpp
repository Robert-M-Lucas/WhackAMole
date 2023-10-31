#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "Player.h"

void register_output(uint8_t stateOne, uint8_t stateTwo);

const int WIN_THRESHOLD = 10;

pin DATA_PIN = 13;
pin CLOCK_PIN = 11;
pin LATCH_PIN = 12;

pin RANDOM_SEED_PIN = A0;

unsigned long interval_ms = 350;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Shift register indexes for player 1
unsigned int p1Leds[3] = {4, 5, 6};
Player p1(p1Leds, 7, 10, &interval_ms);

unsigned int p2Leds[3] = {0, 1, 2};
Player p2(p2Leds, 3, 9, &interval_ms);

unsigned int p3Leds[3] = {0, 1, 2};
Player p3(p3Leds, 3, 8, &interval_ms);

Servo servo;

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

void setup() {
    Serial.begin(9600);

    servo.attach(A5);

    lcd.begin(16, 2);
    lcd.print("Starting game...");
    Serial.println("Starting game");

    pinMode(RANDOM_SEED_PIN, INPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);

    // Set analogue noise as our random seed to ensure unique games
    randomSeed(analogRead(RANDOM_SEED_PIN));

    // Target must be randomised AFTER random seed is set
    p1.randomiseTarget();
    p2.randomiseTarget();
    p3.randomiseTarget();

    // Pre-game delay
    // Clear register
    flash_leds();
    delay(1000);
}

void checkWin() {
    int winner = -1;
    if (p1.getScore() >= WIN_THRESHOLD) {
        winner = 1;
    }
    else if (p2.getScore() >= WIN_THRESHOLD) {
        winner = 2;
    }
    else if (p3.getScore() >= WIN_THRESHOLD) {
        winner = 3;
    }

    if (winner != -1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Game Over!");
        lcd.setCursor(0, 1);
        lcd.print("Player ");
        lcd.print(winner);
        lcd.print(" wins!");
        flash_leds();
        delay(3000);
        lcd.setCursor(0, 0);
        lcd.print("Press reset");
        lcd.setCursor(0, 1);
        lcd.print("to play again");
        while (true) {
            delay(1000);
        }
    }
}

void update(unsigned long tick) {
    p1.update(tick);
    p2.update(tick);
    p3.update(tick);
    servo.write(constrain(map(interval_ms, 200, 400, 0, 180), 0, 180));
    checkWin();
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
    uint8_t registerStateOne = 0b00000000;
    uint8_t registerStateTwo = 0b00000000;
    registerStateOne |= p1.getLedBitFlags();
    registerStateOne |= p2.getLedBitFlags();
    registerStateTwo |= p3.getLedBitFlags();

    register_output(registerStateOne, registerStateTwo);
}

void update_display() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("P1:");
    lcd.print(p1.getScore());
    lcd.print(" 2:");
    lcd.print(p2.getScore());
    lcd.print(" 3:");
    lcd.print(p3.getScore());

    lcd.setCursor(0, 1);
    lcd.print("Level: ");
    lcd.print(interval_ms);
    lcd.print("ms");
}

// Suitable size, will take 50 days to overflow
unsigned long tick = 0;
unsigned long tick_interval = 10;

void loop() {
    update_display();
    for (int _ = 0; _ < 75; _++) {
        update(tick);
        show_leds();
        delay(tick_interval);
        tick += tick_interval;
    }
}