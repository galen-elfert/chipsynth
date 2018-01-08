/*
 * Chip Synth
 * 
 * Teensy based CEM3394 synth chip controller
 * 
 * Created Jan 5 2017
 * Galen Elfert
 */

#define ENC_A_PIN 36
#define ENC_B_PIN 35

typedef struct encoder_state_t 
{
    bool fired_A;
    bool fired_B;
    int increment;
    int last_time;
} encoder_state_t;

volatile encoder_state_t encoder_state;

int last_count = 0;
int enc_A_interrupt;
int enc_B_interrupt;

void encoder_isr_A()
{
    if (encoder_state.fired_B)
    {
        if(millis() - encoder_state.last_time < 100)
        {
            encoder_state.increment++;
        }
        encoder_state.fired_A = 0;
        encoder_state.fired_B = 0;
    } else {
        encoder_state.fired_A = 1;
        encoder_state.last_time = millis();
    }
}

void encoder_isr_B()
{
    if (encoder_state.fired_A)
    {
        if(millis() - encoder_state.last_time < 100)
        {
            encoder_state.increment--;
        }
        encoder_state.fired_A = 0;
        encoder_state.fired_B = 0;
    } else {
        encoder_state.fired_B = 1;
        encoder_state.last_time = millis();
    }
}

void setup() {
    Serial.begin(9600);

    encoder_state.fired_A = 0;    
    encoder_state.fired_B = 0;    
    encoder_state.increment = 0;

    // Set up pins
    pinMode(ENC_A_PIN, INPUT_PULLUP);
    pinMode(ENC_B_PIN, INPUT_PULLUP);

    // Set up interrupt
    enc_A_interrupt = digitalPinToInterrupt(ENC_A_PIN);
    enc_B_interrupt = digitalPinToInterrupt(ENC_B_PIN);
    attachInterrupt(enc_A_interrupt, encoder_isr_A, FALLING);
    attachInterrupt(enc_B_interrupt, encoder_isr_B, FALLING);
}

void loop() {
    // put your main code here, to run repeatedly:
    noInterrupts();
    if(last_count != encoder_state.increment)
    {
        last_count = encoder_state.increment;
        Serial.println(last_count);
    }
    interrupts();
    delay(100);
}
