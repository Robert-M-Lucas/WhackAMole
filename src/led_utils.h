//
// Created by rober on 31/10/2023.
//

#ifndef WHACKAMOLE_LED_UTILS_H
#define WHACKAMOLE_LED_UTILS_H

/// Flash all LEDS on and off repeatedly. Clear shift registers after
void flash_leds();

/// Output data to the two shift register as two 8-bit bitflags
void register_output(unsigned char stateOne, unsigned char stateTwo);

#endif //WHACKAMOLE_LED_UTILS_H
