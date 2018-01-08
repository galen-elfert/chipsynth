/*
 * Chip Synth
 * 
 * Functions for capturing and processing input from rotary encoders/buttons. 
 * 
 * Created Jan 5 2017
 * Galen Elfert
 */

/*
init:
    - register interrupts for A and B pins
    - initialize global increment variables (signed)
    - 
 */

// Global variables to store encoder changes
volatile int cs_input_enc_change = 0;

void cs_input_init(void)
{
    cs_input_enc_change = 0;

    // Register interrupt
}
