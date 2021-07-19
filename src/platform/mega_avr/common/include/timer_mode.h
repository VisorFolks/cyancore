/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: timer_mode_h
 * Description		: This file contains available timer modes enumerated
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _TIMER_MODE_H_

enum timer_mode
{
	normal = 1,
	/*
	 * In certain spec if bit value is not
	 * specified take default to be 8b.
	 */
	timer_pwm_phase_correct_8b = 2,
	timer_pwm_phase_correct_9b = 3,
	timer_pwm_phase_correct_10b = 4,
	/*
	 * In certian spec if icr/ocr is not
	 * specified take default to be ocr
	 */
	ctc_ocr = 5,
	timer_pwm_fast_8b = 6,
	timer_pwm_fast_9b = 7,
	timer_pwm_fast_10b = 8,
	timer_pwm_phase_freq_correct_icr = 9,
	timer_pwm_phase_freq_correct_ocr = 10,
	timer_pwm_phase_correct_icr = 11,
	timer_pwm_phase_correct_ocr = 12,
	ctc_icr = 13,
	timer_pwm_fast_icr = 14,
	timer_pwm_fast_ocr = 15,
};
