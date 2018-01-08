#include "cs_encoder.h"

static volatile int cs_encoder_count;
static volatile int cs_encoder_last_time;

int cs_encoder_pin_A;
int cs_encoder_pin_B;

//static volatile cs_encoder_state_t cs_encoder_state = {0};
static cs_encoder_state_t cs_encoder_state = {0};

void cs_encoder_setup(int pin_A, int pin_B)
{
    cs_encoder_pin_A = pin_A;
    cs_encoder_pin_B = pin_B;
    pinMode(pin_A, INPUT_PULLUP);
    pinMode(pin_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin_A), cs_encoder_interrupt_routine_A, FALLING);
    attachInterrupt(digitalPinToInterrupt(pin_B), cs_encoder_interrupt_routine_B, FALLING);
    cs_encoder_last_time = millis();
}

void cs_encoder_interrupt_routine_A()
{
    if(digitalRead(cs_encoder_pin_B) == HIGH)
    {
        if(millis() - cs_encoder_last_time > CS_ENCODER_DEBOUNCE_TIME)
        {
            cs_encoder_state.count++;
            cs_encoder_last_time = millis();
        } else {
            cs_encoder_state.debounce_A++;
        }
    } else {
        cs_encoder_state.fail_A++;
    }
}

void cs_encoder_interrupt_routine_B()
{
    if(digitalRead(cs_encoder_pin_A) == HIGH)
    {
        if(millis() - cs_encoder_last_time > CS_ENCODER_DEBOUNCE_TIME)
        {
            cs_encoder_state.count--;
            cs_encoder_last_time = millis();
        } else {
            cs_encoder_state.debounce_B++;
        }
    } else {
        cs_encoder_state.fail_B++;
    }
}

cs_encoder_state_t cs_encoder_read_state()
{
    noInterrupts();
    cs_encoder_state_t this_state = cs_encoder_state;
    //cs_encoder_state.fail_A = 0;
    //cs_encoder_state.fail_B = 0;
    //cs_encoder_state.debounce_A = 0;
    //cs_encoder_state.debounce_B = 0;
    interrupts();
    return this_state;
}
