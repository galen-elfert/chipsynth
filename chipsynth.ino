/*
 * Chip Synth
 * 
 * Teensy based CEM3394 synth chip controller
 * 
 * Created Jan 5 2017
 * Galen Elfert
 */
#include "cs_encoder.h"

#define ENC_A_PIN 36
#define ENC_B_PIN 35

cs_encoder_state_t last_state = {0};

void setup() {
    Serial.begin(9600);
    cs_encoder_setup(ENC_A_PIN, ENC_B_PIN);
}

void loop() {
    // put your main code here, to run repeatedly:
    cs_encoder_state_t state = cs_encoder_read_state();
    if(state.count != last_state.count || 
       state.fail_A != last_state.fail_A || state.fail_B != last_state.fail_B ||
       state.debounce_A != last_state.debounce_A || state.debounce_B != last_state.debounce_B)
    {
        Serial.println("9 8 7 6 5 4 3 2 1 0 1 2 3 4 5 6 7 8 9");
        for(int i=-9; i<10; i++)
        {
            if(state.count == i)
            {
                Serial.print("^ ");
            } else {
                Serial.print("  ");
            }
        }
        Serial.println("");
        Serial.print("Count: ");
        Serial.print(state.count);
        Serial.println("");
        Serial.print("Fail A, B: ");
        Serial.print(state.fail_A);
        Serial.print(", ");
        Serial.print(state.fail_B);
        Serial.println("");
        Serial.print("Debounce A, B: ");
        Serial.print(state.debounce_A);
        Serial.print(", ");
        Serial.print(state.debounce_B);
        Serial.println("");
    }
    last_state = state;
    delay(1000);
}
