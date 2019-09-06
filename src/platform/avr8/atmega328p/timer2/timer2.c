/*
 * Author	: Akash Kollipara
 * File		: timer2.c
 * Note		: Implements functions to access timer2 registers
 */

#include <timer2.h>
#include <avr/io.h>
// Timer 2 on/off functions
void timer2_en(uint8_t ticks)
{
		// Power up timer2
		PRR		&= ~(1 << PRTIM2);
		// Enable CTC mode
		TCCR2A	|= (1 << WGM21);
		// Prescale source clock
		TCCR2B	|= (PRESCALER & 0x07);
		// Load max value upto which timer 2 runs
		// After TCNT2 value matches with OCR2A, interrupt is raised
		OCR2A	 = ticks;
		// Clear Timer 2 Counter
		TCNT2	 = 0;
}

void timer2_dis()
{
		// Disable clock source to Timer 2
		TCCR2B	&= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
		TCNT2	 = 0;
		// Shut down Timer 2
		PRR		|= (1 << PRTIM2);
}


// Timer 2 interrupt enable/disable functions
void timer2_int_en()
{
		TIMSK2	|= (1 << OCIE2A);
}

void timer2_int_dis()
{
		TIMSK2	&= ~(1 << OCIE2A);
}


// Timer 2 Counter value
unsigned int timer2_counter()
{
		return TCNT2;
}

