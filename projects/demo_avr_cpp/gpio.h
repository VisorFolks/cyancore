/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: gpio.h
 * Description		: This file consists of gpio on board led class
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

class onBoardLed
{
	private:
		gpio_port_t led13;
	public:
		onBoardLed();
		void setup();
		void toggle();
};
