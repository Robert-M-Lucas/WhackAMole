//
// Created by rober on 28/10/2023.
//

#include "Player.h"
#include <Arduino.h>
#include "definitions.h"
#include "constants.h"


Player::Player(unsigned int ledIndexes[3], unsigned int successLedIndex, pin inputPin, unsigned long* interval):
    ledIndexes{ledIndexes[0], ledIndexes[1], ledIndexes[2]}, successLedIndex(successLedIndex), inputPin(inputPin), interval(interval) {
    pinMode(inputPin, INPUT);
}

void Player::setLedOn(unsigned int shiftRegisterIndex) {
    ledStates |= 1 << shiftRegisterIndex;
}

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
    else if (time_without_target < SHOW_TARGET_TIME + ALL_LEDS_OFF_PERIOD) {}
    // Normal play
    else {
        if (digitalRead(inputPin) == HIGH) {
            if (randomLedStates[target]) {
                lastPointScored = true;
                score += 1;
                *interval -= INTERVAL_DECREMENT_ON_POINT;
            } else {
                lastPointScored = false;
                score -= 1;
                *interval += INTERVAL_DECREMENT_ON_POINT;
            }

            randomiseTarget();
            showingTargetStart = tick;
        }
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
