/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: stddev.h
 * Description		: This file contains prototypes and macros of 
 *			  standard devices
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STDDEV_H_

status_t stdin_register(status_t (*)(char *));
status_t stdout_register(status_t (*)(const char));
status_t stderr_register(status_t (*)(const char));
status_t stdlog_register(status_t (*)(const char));
