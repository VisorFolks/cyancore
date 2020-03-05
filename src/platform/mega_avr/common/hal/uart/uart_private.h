#pragma once

#define FCLK	16000000

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

#if FCLK==16000000
#define	B2400		416
#define	B4800		207
#define	B9600		103
#define	B19200		51
#define	B38400		25
#define B115200		8
#define	B230400		3
#define	B250000		3
#endif
