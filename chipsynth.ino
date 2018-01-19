/*
 * Chip Synth
 * 
 * Teensy based CEM3394 synth chip controller
 * 
 * Created Jan 5 2017
 * Galen Elfert
 */

#include "cs_encoder.h"
#include "cs_lcd.h"
#include "cs_voice.h"

#define ENC_A_PIN 36
#define ENC_B_PIN 35

int count = 0;

void setup() {
    Serial.begin(9600);
    cs_encoder_setup(ENC_A_PIN, ENC_B_PIN);
}

void loop() {
    // put your main code here, to run repeatedly:
    int increment = cs_encoder_read_count();
    if(increment != 0)
    {
        count += increment;
        Serial.println("9 8 7 6 5 4 3 2 1 0 1 2 3 4 5 6 7 8 9");
        for(int i=-9; i<10; i++)
        {
            if(count == i)
            {
                Serial.print("^ ");
            } else {
                Serial.print("  ");
            }
        }
        Serial.println("");
    }
    /*delay(100);*/
}
