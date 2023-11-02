//
// Created by robertlucas on 02/11/23.
//

#include "difficulty.h"
#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include "constants.h"

/// Helper function for pick_game_difficulty to display to the lcd
void display(LiquidCrystal *lcd, unsigned long interval, int seconds_remaining) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Init. Lvl: ");
    lcd->print(interval);
    lcd->print("ms");

    lcd->setCursor(0, 1);
    lcd->print("Starting in: ");
    lcd->print(seconds_remaining);
    lcd->print("s");
}

unsigned long pick_game_difficulty(LiquidCrystal *lcd, Servo *servo) {
    int millis_remaining = DIFFICULTY_PICK_TIME_MS;
    unsigned long interval = 300;
    unsigned long prev_interval = interval;

    while (millis_remaining > 0) {
        // Convert analogue reading 0 - 1023 to difficulty MIN - MAX
        interval = map(analogRead(DIFFICULTY_PIN), 0, 1023, MINIMUM_DIFFICULTY, MAXIMUM_DIFFICULTY);

        if (interval != prev_interval) {
            display(lcd, interval, millis_remaining / 1000);
        }

        servo->write(constrain(map(interval, MINIMUM_DIFFICULTY, MAXIMUM_DIFFICULTY, 0, 180), 0, 180));

        delay(200);
        millis_remaining -= 200;
    }

    return interval;
}
