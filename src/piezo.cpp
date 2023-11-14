#include <Arduino.h>
#include "constants.h"
#include "tones.h"

void play_game_start_sound() {
    Serial.println("Playing game start sound");
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
    Serial.println("Playing game end sound");
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
    Serial.println("Playing point scored sound");
    tone(PIEZO_PIN, NOTE_A5, 100);
}

void play_point_lost_sound() {
    Serial.println("Playing point lost sound");
    tone(PIEZO_PIN, NOTE_A2, 100);
}
