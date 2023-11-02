//
// Created by robertlucas on 02/11/23.
//

#include "instructions.h"
#include <Arduino.h>
#include "constants.h"

void show_instructions(LiquidCrystal *lcd) {
    const char* text = "Instructions: An LED will flash - this is your target. When the flashing stops, press your button when the target lights up. The next target will then appear";
    const int length = 157;

    lcd->clear();

    int index = 0;
    bool exit_next = false;
    while (true) {
        lcd->clear();
        lcd->setCursor(0, 0);

        for (int i = 0; i < 16; i++) {
            lcd->print(text[index + i]);
        }
        lcd->setCursor(0, 1);
        lcd->print("Skip: hold btn");

        if (index == 0) { delay(2000); }

        if (exit_next) { break; }

        index += 2;
        if (index > length - 16) {
            index = length - 16;
            exit_next = true;
        }

        delay(500);

        if (digitalRead(P1_BTN) == HIGH ||
                digitalRead(P2_BTN) == HIGH ||
                digitalRead(P3_BTN) == HIGH) {
            return;
        }
    }

    delay(2000);
}
