//
// Created by rober on 28/10/2023.
//

#include "Player.h"
#include <Arduino.h>
#include "definitions.h"
#include "constants.h"
#include "piezo.h"


Player::Player(unsigned int ledIndexes[3], unsigned int successLedIndex, pin inputPin, unsigned long* interval):
    ledIndexes{ledIndexes[0], ledIndexes[1], ledIndexes[2]}, successLedIndex(successLedIndex), inputPin(inputPin), interval(interval) {
    pinMode(inputPin, INPUT);
}

/// Sets the LED bitflag at the given position to on
void Player::setLedOn(unsigned int shiftRegisterIndex) {
    ledStates |= 1 << shiftRegisterIndex;
}

/// PLayer update loop
void Player::update(unsigned long tick) {
    ledStates = 0;
    unsigned long time_without_target = tick - showingTargetStart;

    // Showing next target
    if (time_without_target < SHOW_TARGET_TIME) {
        // Blink new target every 500ms
        if ((time_without_target / TARGET_BLINK_INTERVAL) % 2 == 0) {
            setLedOn(ledIndexes[target]);
        }

        // Show whether the last button press was successful
        if (lastPointScored) {
            setLedOn(successLedIndex);
        }
    }
    // Show nothing for a short period
    else if (time_without_target < SHOW_TARGET_TIME + ALL_LEDS_OFF_PERIOD) {}
    // Normal play
    else {
        // On button press
        if (digitalRead(inputPin) == HIGH) {
            // Point is scored (target LED is on)
            if (randomLedStates[target]) {
                lastPointScored = true;
                score += 1;
                *interval -= INTERVAL_DECREMENT_ON_POINT; // Adjust difficulty
                play_point_scored_sound();
            }
            // No point scored
            else {
                lastPointScored = false;
                score -= 1;
                if (score < -9) score = -9;
                *interval += INTERVAL_DECREMENT_ON_POINT; // Adjust difficulty
                play_point_lost_sound();
            }

            randomiseTarget();
            showingTargetStart = tick;
        }
        // On no button press
        else  {
            if (tick - randomShowStart > *interval) {
                randomShowStart = tick;

                for (int i = 0; i < 3; i++) {
                    if (i == target) {
                        randomLedStates[i] = random(5) == 0;
                    }
                    else {
                        randomLedStates[i] = random(2) == 0;
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                if (randomLedStates[i]) {
                    setLedOn(ledIndexes[i]);
                }
            }
        }
    }
}

uint8_t Player::getLedBitFlags() const {
    return ledStates;
}

void Player::randomiseTarget() {
    target = (int) random(3);
}

int Player::getScore() const {
    return score;
}
