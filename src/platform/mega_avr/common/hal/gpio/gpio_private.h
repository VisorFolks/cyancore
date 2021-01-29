#pragma once
#define _GPIO_PRIVATE_H_

#define PIN_OFFSET	0x00
#define DDR_OFFSET	0x01
#define PORT_OFFSET	0x02

lock_t gpio_lock;
uint8_t port_status[N_PORT];

