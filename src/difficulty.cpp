//
// Created by robertlucas on 02/11/23.
//

#include "difficulty.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "constants.h"

void display(LiquidCrystal *lcd, unsigned long interval, int seconds_remaining) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(interval);

    lcd->setCursor(0, 1);
    lcd->print("Starting in: ");
    lcd->print(seconds_remaining);
    lcd->print("s");
}

unsigned long pick_game_difficulty(LiquidCrystal *lcd) {
    int millis_remaining = 10000;
    unsigned long interval = 300;

    while (millis_remaining > 0) {
        interval = map(analogRead(DIFFICULTY_PIN), 0, 1023, 200, 500);
        display(lcd, interval, millis_remaining / 1000);

        delay(200);
        millis_remaining -= 200;
    }

    return interval;
}
