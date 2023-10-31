//
// Created by rober on 28/10/2023.
//

#ifndef WHACKAMOLE_PLAYER_H
#define WHACKAMOLE_PLAYER_H

#include <Arduino.h>
#include "definitions.h"

class Player {
    /// Stores the shift register output indexes for each LED
    unsigned int ledIndexes[3];
    /// Stores the shift register output indexes for the point gained LED
    unsigned int successLedIndex;

    /// State of LEDs while they are randomly blinking
    bool randomLedStates[3];
    /// When the LEDs were last randomised
    unsigned long randomShowStart = 0;

    /// LED states as bitflags ready for the shift register
    uint8_t ledStates = 0;

    /// When the target started to be shown
    unsigned long showingTargetStart = 0;
    int target = 0;

    bool lastPointScored = false;

    pin inputPin;

    int score = 0;

private:
    /// Sets the corresponding ledStates bitflag to true
    void setLedOn(unsigned int shiftRegisterIndex);

public:
    Player(unsigned int ledIndexes[3], unsigned int successLedIndex, pin inputPin);

    void randomiseTarget();

    void update(unsigned long tick);

    uint8_t getLedBitFlags();

    int getScore() const;
};


#endif //WHACKAMOLE_PLAYER_H
