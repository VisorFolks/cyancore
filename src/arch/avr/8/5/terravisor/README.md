# AVR5 - 8 [Terravisor]

Home directory for avr5 terravisor sources.

For terravisor documentation please read [Terravisor README](../../../../visor/terravisor/README.md)

#### Highlights
* Bootstrap routine is written in C
* Minimal use of assembly
* Interrupt handlers (int ID: 1 - n) will be automatically allocated based on platform vectors
* Implemented busy loop spinlock so that interrupts are not blocked while executing critical sections
* Soft implementation of higher architecture CPU feature to perform machine call
