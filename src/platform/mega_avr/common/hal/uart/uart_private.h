#pragma once

// This is necessary
#ifndef	FCLK
#error < x > FCLK is not defined...
#endif

#define	UCSRA_OFFSET	0x0
#define	UCSRB_OFFSET	0x1
#define	UCSRC_OFFSET	0x2
#define	UBRRL_OFFSET	0x4
#define	UBRRH_OFFSET	0x5
#define	UDR_OFFSET	0x6

#define BAUD_RATE_VALUE(X)	(uint16_t)(((FCLK + ((X) << 3)) / ((X) << 4) - 1))

/**
 * UCSRA Register bitfields
 */
#define	MPCM	0
#define	U2X	1
#define	UPE	2
#define	DOR	3
#define	FE	4
#define	UDRE	5
#define	TXC	6
#define RXC	7

/**
 * UCSRB Register bitfields
 */
#define	TXB8	0
#define	RXB8	1
#define	UCSZ2	2
#define	TXEN	3
#define	RXEN	4
#define	UDRIE	5
#define	TXCIE	6
#define	RXCIE	7

/**
 * UCSRC Register bitfields
 */
#define	UCPOL	0
#define	UCSZ0	1
#define	UCSZ1	2
#define	USBS	3
#define	UPM0	4
#define	UPM1	5
#define	UMSEL0	6
#define	UMSEL1	7
