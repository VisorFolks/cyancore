/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: gpio.cpp
 * Description		: This file consists of gpio on board led driver in cpp
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

extern "C"
{
	#include <status.h>
	#include <hal/gpio.h>
}

#include "gpio.h"

/* Outside declaration of the member function of class onBoardLed */
void onBoardLed::setup()
{
	gpio_pin_alloc(&led13, 0, 5);
	gpio_pin_mode(&led13, out);
	gpio_pin_clear(&led13);
}

void onBoardLed::toggle()
{
	gpio_pin_toggle(&led13);
}
