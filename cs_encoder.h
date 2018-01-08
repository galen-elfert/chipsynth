#ifndef _CS_ENCODER_H
#define _CS_ENCODER_H

#include "Arduino.h"

#define CS_ENCODER_DEBOUNCE_TIME 10

typedef struct cs_encoder_state_t
{
    int count;
    int debounce_A;
    int debounce_B;
    int fail_A;
    int fail_B;
} cs_encoder_state_t;

void cs_encoder_setup(int pin_A, int pin_B);

void cs_encoder_interrupt_routine_A();
void cs_encoder_interrupt_routine_B();

cs_encoder_state_t cs_encoder_read_state();

#endif /* ifndef _CS_ENCODER_H */
