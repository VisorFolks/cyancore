/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: gpio_bit_banding.c
 * Description		: This file consists of gpio sources using bit banding
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/* 8bit Register */
typedef struct reg8
{
	unsigned char b0:1;
	unsigned char b1:1;
	unsigned char b2:1;
	unsigned char b3:1;
	unsigned char b4:1;
	unsigned char b5:1;
	unsigned char b6:1;
	unsigned char b7:1;
} reg8_t;


/* Pointers for gpio registers */
static reg8_t *ddrb, *portb;

void gpio_init()
{
	/* Statically programming the addresses */
	ddrb = (reg8_t *)0x24;		// ATMEGA328P DDRB address
	portb = (reg8_t *)0x25;		// ATMEGA328P PORTB address

	/* Configure pin 5 as output */
	ddrb->b5 = 1;
}

void gpio_toggle()
{
	/* Toggle pin 5 */
	portb->b5 ^=1;
}
