/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: onboardled.h
 * Description		: This file consists of onboardled
 *			  driver prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _ONBOARDLED_H_

status_t onboardled_toggle(void);
status_t onboardled_on(void);
status_t onboardled_off(void);
