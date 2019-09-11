#pragma once

#define __AVR_ATMEGA328P__
#define ARCH_AVR

#define PROG_MEM	0X0000
#define IMEM_START	0x0000
#define IMEM_LENGTH	0x4000
#define DMEM_START	0x4000
#define DMEM_LENGTH	0x4000
#define STACK_SIZE	0x400

//===============< Register Addresses >===============//

#define PINB		0x23
#define DDRB		0x24
#define PORTB		0x25

#define PINC		0x26
#define DDRC		0x27
#define PORTC		0x28

#define PIND		0x29
#define DDRD		0x2a
#define PORTD		0x2b

#define TIFR0		0x35
#define TIFR1		0x36
#define TIFR2		0x37

#define PCIFR		0x3b

#define EIFR		0x3c
#define EIMSK		0x3d

#define GPIOR0		0x3e

#define EECR		0x3f
#define EEDR		0x40

#define EEARL		0x41
#define EEARH		0x42

#define GTCCR		0x43

#define TCCR0A		0x44
#define TCCR0B		0x45
#define TCNT0		0x46
#define OCR0A		0x47
#define OCR0B		0x48

#define GPIOR1		0x4a
#define GPIOR2		0x4b

#define SPCR		0x4c
#define SPDR		0x4d

#define ACSR		0x50

#define SMCR		0x53

#define MCUSR		0x54
#define MCUCR		0x55

#define SPMCSR		0x57

#define SPL		0x5d
#define SPH		0x5e
#define SREG		0x5f

#define WDTCSR		0x60
#define CLKPR		0x61

#define PRR		0x64

#define OSCCAL		0x66

#define PCMASK0		0x6b
#define PCMASK1		0x6c
#define PCMASK2		0x6d

#define TIMSK0		0x6e
#define TIMSK1		0x6f
#define TIMSK2		0x70

#define ADCL		0x78
#define ADCH		0x79
#define ADCSRA		0x7a
#define ADCSRB		0x7b
#define ADMUX		0x7c

#define DIDR0		0x7e
#define DIDR1		0x7f

#define TCCR1A		0x80
#define TCCR1B		0x81
#define TCCR1C		0x82
#define TCNT1L		0x84
#define TCNT1H		0x85
#define ICR1L		0x86
#define ICR1H		0x87
#define OCR1AL		0x88
#define OCR1AH		0x89
#define OCR1BL		0x90
#define OCR1BH		0x91

#define TCCR2A		0xb0
#define TCCR2B		0xb1
#define TCNT2		0xb2
#define OCR2A		0xb3
#define OCR2B		0xb4

#define ASSR		0xb6

#define TWBR		0xb8
#define TWSR		0xb9
#define TWAR		0xba
#define TWDR		0xbb
#define TWCR		0xbc
#define TWAMR		0xbd

#define UCSR0A		0xc0
#define UCSR0B		0xc1
#define UCSR0C		0xc2
#define UBRR0L		0xc4
#define UBRR0H		0xc5
#define UDR0		0xc6

//====================================================//
