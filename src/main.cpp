#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "Player.h"
#include "constants.h"
#include "led_utils.h"
#include "piezo.h"
#include "difficulty.h"

unsigned long led_interval = 300;

// Initialise LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Shift register indexes for player 1 leds
unsigned int p1Leds[3] = {4, 5, 6};
Player p1(p1Leds, 7, 10, &led_interval);

// sim.
unsigned int p2Leds[3] = {0, 1, 2};
Player p2(p2Leds, 3, 9, &led_interval);

unsigned int p3Leds[3] = {0, 1, 2};
Player p3(p3Leds, 3, 8, &led_interval);

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

    servo.attach(A5);

    lcd.begin(16, 2);
    lcd.print("Starting game...");
    Serial.println("Starting game");


    // Target must be randomised AFTER random seed is set
    p1.randomiseTarget();
    p2.randomiseTarget();
    p3.randomiseTarget();

    // Pre-game delay + shift register clear
    flash_leds();
    led_interval = pick_game_difficulty(&lcd, &servo); // Allow the user to set the difficulty
    play_game_start_sound();

    // Offset the builtin millis() function to be at 0 when gameplay starts
    tick_offset = millis();
}

/// Do nothing forever
[[noreturn]] void waitForever() {
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
    p1.update(tick);
    p2.update(tick);
    p3.update(tick);

    led_interval = constrain(led_interval, MINIMUM_GAMEPLAY_DIFFICULTY, MAXIMUM_DIFFICULTY);
    servo.write(constrain(map(led_interval, 200, 400, 0, 180), 0, 180));
    check_win();
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

unsigned long tick_interval = 10;
unsigned int lcd_update_interval = 75;

void loop() {
    update_lcd(); // Run LCD update less frequently as it takes longer to refresh

    for (unsigned int _ = 0; _ < lcd_update_interval; _++) {
        update(millis() - tick_offset);
        show_leds();
        delay(tick_interval);
    }
}