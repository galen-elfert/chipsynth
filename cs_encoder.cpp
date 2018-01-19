/*
 * Chip Synth
 * 
 * Teensy based CEM3394 synth chip controller
 * 
 * Created Jan 5 2017
 * Galen Elfert
 */

#include "cs_encoder.h"

static volatile int cs_encoder_count;
static volatile int cs_encoder_last_time;

int cs_encoder_pin_A;
int cs_encoder_pin_B;

//static volatile cs_encoder_state_t cs_encoder_state = {0};
//static cs_encoder_state_t cs_encoder_state = {0};

void cs_encoder_setup(int pin_A, int pin_B)
{
    cs_encoder_pin_A = pin_A;
    cs_encoder_pin_B = pin_B;
    pinMode(pin_A, INPUT_PULLUP);
    pinMode(pin_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin_A), cs_encoder_isr_A, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pin_B), cs_encoder_isr_B, CHANGE);
    cs_encoder_last_time = millis();
    cs_encoder_count = 0;
}

void cs_encoder_isr_A()
{
    if(digitalRead(cs_encoder_pin_A) == LOW && digitalRead(cs_encoder_pin_B) == HIGH)
    {
        if(millis() - cs_encoder_last_time > CS_ENCODER_DEBOUNCE_TIME)
        {
            cs_encoder_count++;
        }
    }
    cs_encoder_last_time = millis();
}

void cs_encoder_isr_B()
{
    if(digitalRead(cs_encoder_pin_B) == LOW && digitalRead(cs_encoder_pin_A) == HIGH)
    {
        if(millis() - cs_encoder_last_time > CS_ENCODER_DEBOUNCE_TIME)
        {
            cs_encoder_count--;
        }
    }
    cs_encoder_last_time = millis();
}

int cs_encoder_read_count()
{
    noInterrupts();
    int this_count = cs_encoder_count;
    cs_encoder_count = 0;
    interrupts();
    return this_count;
}
