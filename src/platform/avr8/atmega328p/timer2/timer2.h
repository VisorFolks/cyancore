/*
 * Author	: Akash Kollipara
 * File		: timer2.h
 * Note		: Header file for timer2.c
 */

#ifndef timer2_h
#define timer2_h

#define TIMER2_PRESCALER_1     1
#define TIMER2_PRESCALER_8     2
#define TIMER2_PRESCALER_32    3
#define TIMER2_PRESCALER_64    4
#define TIMER2_PRESCALER_128   5
#define TIMER2_PRESCALER_256   6
#define TIMER2_PRESCALER_1024  7

// Timer 2 on/off functions
void timer2_en(uint8_t);
void timer2_dis();

// Timer 2 interrupt enable/disable functions
void timer2_int_en();
void timer2_int_dis();

// Timer 2 Counter value
unsigned int timer2_counter();

#endif
