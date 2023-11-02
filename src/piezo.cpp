//
// Created by robertlucas on 31/10/23.
//

#include <Arduino.h>
#include "constants.h"
#include "tones.h"

void play_game_start_sound() {
    tone(PIEZO_PIN, NOTE_A3, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_CS4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_E4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_A4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_E4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_CS4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_A3, 250);
}

void play_game_end_sound() {
    tone(PIEZO_PIN, NOTE_A4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_E4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_CS4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_A3, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_CS4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_E4, 250);
    delay(300);
    tone(PIEZO_PIN, NOTE_A4, 250);
}

void play_point_scored_sound() {
    tone(PIEZO_PIN, NOTE_A5, 100);
}

void play_point_lost_sound() {
    tone(PIEZO_PIN, NOTE_A2, 100);
}
