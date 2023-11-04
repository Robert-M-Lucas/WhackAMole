//
// Created by robertlucas on 02/11/23.
//

#include "instructions.h"
#include <Arduino.h>
#include "constants.h"

void show_instructions(LiquidCrystal *lcd) {
    Serial.println("Showing instructions");

    const char* text = "*Skip: hold btn*"
                       "Instructions:   "
                       "An LED will     "
                       "flash - this    "
                       "is your         "
                       "target. When the"
                       "flashing stops, "
                       "press your      "
                       "button when the "
                       "target lights up"
                       ". The next      "
                       "target will then"
                       "appear         ";

    lcd->clear();

    int index = 0;
    bool exit_next = false;
    while (true) {
        lcd->clear();
        lcd->setCursor(0, 0);

        // Print scrolling text
        for (int i = 0; i < 32; i++) {
            // Check for end of string
            if (text[index + i] == '\0') {
                exit_next = true;
                break;
            }

            if (i == 16) lcd->setCursor(0, 1);

            lcd->print(text[index + i]);
        }

        // Longer delay before the text starts moving
        if (index == 0) { delay(3000); }

        if (exit_next) { break; }

        index += 16;

        delay(2000);

        // Check for instruction skip
        if (digitalRead(P1_BTN) == HIGH ||
                digitalRead(P2_BTN) == HIGH ||
                digitalRead(P3_BTN) == HIGH) {
            Serial.println("Skipping instructions");
            return;
        }
    }

    delay(2000);
}
