#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "Player.h"
#include "constants.h"
#include "led_utils.h"
#include "piezo.h"
#include "difficulty.h"
#include "instructions.h"

unsigned long led_interval = 300;

// Initialise LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Shift register indexes for player 1 leds
unsigned int p1Leds[3] = {4, 5, 6};
Player p1(1, p1Leds, 7, P1_BTN, &led_interval);

// sim.
unsigned int p2Leds[3] = {0, 1, 2};
Player p2(2, p2Leds, 3, P2_BTN, &led_interval);

unsigned int p3Leds[3] = {0, 1, 2};
Player p3(3, p3Leds, 3, P3_BTN, &led_interval);

Servo servo;

unsigned long tick_offset = 0;

void setup() {
    pinMode(RANDOM_SEED_PIN, INPUT);
    pinMode(SR_CLOCK_PIN, OUTPUT);
    pinMode(SR_DATA_PIN, OUTPUT);
    pinMode(SR_LATCH_PIN, OUTPUT);

    // Set analogue noise as our random seed to ensure unique games
    randomSeed(analogRead(RANDOM_SEED_PIN));

    Serial.begin(9600);
    Serial.println("[RESTART]");
    print_config();

    servo.attach(A5);

    lcd.begin(16, 2);
    lcd.print("Starting game...");

    // Pre-game delay + shift register clear
    flash_leds();

    show_instructions(&lcd);

    led_interval = pick_game_difficulty(&lcd, &servo); // Allow the user to set the difficulty

    play_game_start_sound();

    // Target must be randomised AFTER random seed is set
    p1.randomiseTarget();
    p2.randomiseTarget();
    p3.randomiseTarget();

    // Offset the builtin millis() function to be at 0 when gameplay starts
    tick_offset = millis();
    Serial.print("Tick offset: "); Serial.println(tick_offset);

    Serial.println("Game start");
}

/// Do nothing forever
[[noreturn]] void waitForever() {
    Serial.println("Waiting forever");
    while (true) { delay(1000); }
}

/// Checks for a winning player
void check_win() {
    int winner = -1;
    if (p1.getScore() >= WIN_THRESHOLD) {
        winner = 1;
    }
    else if (p2.getScore() >= WIN_THRESHOLD) {
        winner = 2;
    }
    else if (p3.getScore() >= WIN_THRESHOLD) {
        winner = 3;
    }

    if (winner != -1) {
        Serial.println("Game ended");
        Serial.print("Player "); Serial.print(winner); Serial.println(" won");
        Serial.println("Showing win text");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Game Over!");
        lcd.setCursor(0, 1);
        lcd.print("Player ");
        lcd.print(winner);
        lcd.print(" wins!");
        flash_leds();
        play_game_end_sound();
        delay(3000);

        Serial.println("Showing restart text");
        lcd.setCursor(0, 0);
        lcd.print("Press reset");
        lcd.setCursor(0, 1);
        lcd.print("to play again");

        waitForever();
    }
}

/// Updates leds
void show_leds() {
    // Get register output state as bit flags
    uint8_t registerStateOne = 0b00000000;
    uint8_t registerStateTwo = 0b00000000;
    registerStateOne |= p1.getLedBitFlags();
    registerStateOne |= p2.getLedBitFlags();
    registerStateTwo |= p3.getLedBitFlags();

    register_output(registerStateOne, registerStateTwo);
}

/// Updates the game state
void update(unsigned long tick) {
    // Update the players
    p1.update(tick);
    p2.update(tick);
    p3.update(tick);

    int highest_score = 0;
    highest_score = max(highest_score, p1.getScore());
    highest_score = max(highest_score, p2.getScore());
    highest_score = max(highest_score, p3.getScore());

    // Make sure that the difficulty isn't out of bounds
    led_interval = constrain(led_interval, MINIMUM_GAMEPLAY_DIFFICULTY, MAXIMUM_GAMEPLAY_DIFFICULTY);
    // Show highest score on servo
    servo.write((int) map(constrain(highest_score, 0, WIN_THRESHOLD), 0, WIN_THRESHOLD, 0, 180));

    if (highest_score >= WIN_THRESHOLD) check_win();
}

/// Updates the LCD display
void update_lcd() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("P1:");
    lcd.print(p1.getScore());
    lcd.print(" 2:");
    lcd.print(p2.getScore());
    lcd.print(" 3:");
    lcd.print(p3.getScore());

    lcd.setCursor(0, 1);
    lcd.print("Level: ");
    lcd.print(led_interval);
    lcd.print("ms");
}

unsigned long tick_interval = 5;
unsigned int lcd_update_interval = 150;

void loop() {
    update_lcd(); // Run LCD update less frequently as it takes longer to refresh

    for (unsigned int _ = 0; _ < lcd_update_interval; _++) {
        update(millis() - tick_offset);
        show_leds();
        delay(tick_interval);
    }
}