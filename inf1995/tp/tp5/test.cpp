#include <avr/io.h>
#include <avr/interrupt.h>

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

// initialize timer, interrupt and variable
void timer1_init()
{
    // set up timer with prescaler = 8
    TCCR1B |= ((1 << WGM12) |(0 << CS11) |(1 << CS12));
    // TCCR1C = 0;

    // initialize counter
    TCNT1 = 0;

    // enable overflow interrupt
    TIMSK1 |= (1 << OCIE1A);

    OCR1A = 60000;

    PORTC = 0x02;

    // enable global interrupts
    sei();
}

// TIMER1 overflow interrupt service routine
// called whenever TCNT1 overflows
ISR(TIMER1_COMPA_vect)
{
  PORTC = 0x01;
    // // keep a track of number of overflows
    // tot_overflow++;
    //
    // // check for number of overflows here itself
    // // 61 overflows = 2 seconds delay (approx.)
    // if (tot_overflow >= 61) // NOTE: '>=' used instead of '=='
    // {
    //     PORTC ^= (1 << 0);  // toggles the led
    //     // no timer reset required here as the timer
    //     // is reset every time it overflows
    //
    //     tot_overflow = 0;   // reset overflow counter
    // }
}

int main(void)
{
    // connect led to pin PC0
    DDRC = 0xff;

    // initialize timer
    timer1_init();

    // loop forever
    while(1)
    {
        // do nothing
        // comparison is done in the ISR itself
    }
}
