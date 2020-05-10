#pragma once
#define _SPI_PRIVATE_H_

// Register offsets
#define SPCR_OFFSET	0x00
#define SPSR_OFFSET	0x01
#define SPDR_OFFSET	0x02

/**
 *  Clock division factors
 */
#define fdiv4		0x00
#define fdiv16		0x01
#define fdiv64		0x02
#define fdiv128		0x03

/**
 *  SPCR Register bitfields
 */
#define SPR0		0
#define SPR1		1
#define CPHA		2
#define CPOL		3
#define MSTR		4
#define DODR		5
#define SPE		6
#define SPIE		7

/**
 * SPSR Register bitfields
 */
#define SPI2X		0
#define WCOL		6
#define SPIF		7