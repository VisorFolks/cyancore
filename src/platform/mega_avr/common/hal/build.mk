#
# CYANCORE LICENSE
# Copyrights (C) 2019-2022, Cyancore Team
#
# File Name		: build.mk
# Description		: This file accumulates HAL sources from mega-avr
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#======================================================================
# Configuration file for Platforms
#======================================================================
# Do not make changes to this file or variables

HAL_DIR	:= $(GET_PATH)

include $(HAL_DIR)/clkctl/build.mk
include $(HAL_DIR)/gpio/build.mk
include $(HAL_DIR)/adc/build.mk
include $(HAL_DIR)/eeprom/build.mk
include $(HAL_DIR)/i2c/build.mk
include $(HAL_DIR)/pcint/build.mk
include $(HAL_DIR)/spi/build.mk
include $(HAL_DIR)/timer/build.mk
include $(HAL_DIR)/uart/build.mk
include $(HAL_DIR)/wdt/build.mk
include $(HAL_DIR)/pwm/build.mk
