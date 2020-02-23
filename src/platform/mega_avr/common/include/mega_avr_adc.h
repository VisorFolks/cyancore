#pragma once

#define ADCL_OFFSET	0x00
#define ADCH_OFFSET	0x01
#define ADCSRA_OFFSET	0x02
#define ADCSRB_OFFSET	0x03
#define ADMUX_OFFSET	0x04
#define DIDR2_OFFSET	0x05
#define DIDR0_OFFSET	0x06
#define DIDR1_OFFSET	0x07

// PRR bit field
#define PRADC		0
// ADCSRA bit fields
#define ADEN		7
#define ADSC		6
#define ADATE		5
#define ADIE		3
// ADMUX bit fields
#define REFS		6
#define ADLAR		5
