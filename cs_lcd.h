
/*
 * Chip Synth
 * 
 * Teensy based CEM3394 synth chip controller
 *
 * This file defines functions for setting up and drawing to the LCD screen. 
 *
 * Note:
 *   12864 LCD pin labelling:
 *     E:   clock
 *     R/W: data
 *     RS:  chip select (CS)
 *     PSB: parallel/serial select. LOW for serial. 
 *
 * Created Jan 9 2017
 * Galen Elfert
 */

#include <U8g2lib.h>

// Macros
// Pin assignments

#define CS_LCD_PIN_RS 10
#define CS_LCS_PIN_RW 11
#define CS_LCD_PIN_E  12

void cs_lcd_init();
