//
// Created by rober on 28/10/2023.
//

#include "Player.h"
#include <Arduino.h>
#include "definitions.h"

Player::Player(unsigned int ledIndexes[3], unsigned int successLedIndex, pin inputPin):
    ledIndexes{ledIndexes[0], ledIndexes[1], ledIndexes[2]}, successLedIndex(successLedIndex), inputPin(inputPin) {
    pinMode(inputPin, INPUT);
}

void Player::setLedOn(unsigned int shiftRegisterIndex) {
    ledStates |= 1 << shiftRegisterIndex;
}

void Player::update(unsigned long tick) {
    ledStates = 0;
    unsigned long time_without_target = tick - showingTargetStart;


    // Showing next target
    if (time_without_target < 3000) {
        // Blink new target every 500ms
        if ((time_without_target / 500) % 2 == 0) {
            setLedOn(ledIndexes[target]);
        }

        // Show whether the last button press was successful
        if (lastPointScored) {
            setLedOn(successLedIndex);
        }
    }
    else if (time_without_target < 4000) {}
    // Normal play
    else {
        if (digitalRead(inputPin) == HIGH) {
            if (randomLedStates[target]) {
                lastPointScored = true;
                score += 1;
            } else {
                lastPointScored = false;
            }

            randomiseTarget();
            showingTargetStart = tick;
        }
        else  {
            if (tick - randomShowStart > 500) {
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

uint8_t Player::getLedBitFlags() {
    return ledStates;
}

void Player::randomiseTarget() {
    target = random(3);
}

unsigned int Player::getScore() {
    return score;
}
