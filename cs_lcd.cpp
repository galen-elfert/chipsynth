/*
 * Chip Synth
 * 
 * Teensy based CEM3394 synth chip controller
 *
 * This file defines functions for setting up and drawing to the LCD screen. 
 * 
 * Created Jan 12 2017
 * Galen Elfert
 */

#include "cs_lcd.h"

// Function definitions

void cs_lcd_init()
{
    U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, CS_LCD_PIN_E, CS_LCD_PIN_RW, CD_LCD_PIN_RW, U8X8_PIN_NONE);
}
