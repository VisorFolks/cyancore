#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
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

ifeq ($(CLKCTL),1)
$(eval $(call add_define,CLKCTL))
include $(HAL_DIR)/clkctl/build.mk
endif

ifeq ($(GPIO),1)
$(eval $(call add_define,GPIO))
include $(HAL_DIR)/gpio/build.mk
endif

ifeq ($(ADC0),1)
$(eval $(call add_define,ADC0))
include $(HAL_DIR)/adc/build.mk
endif

ifeq ($(EEPROM),1)
$(eval $(call add_define,EEPROM))
include $(HAL_DIR)/eeprom/build.mk
endif

ifeq ($(I2C0),1)
$(eval $(call add_define,I2C0))
include $(HAL_DIR)/i2c/build.mk
endif

ifeq ($(PCINT0),1)
$(eval $(call add_define,PCINT0))
include $(HAL_DIR)/pcint/build.mk
endif

ifeq ($(SPI0),1)
$(eval $(call add_define,SPI0))
include $(HAL_DIR)/spi/build.mk
endif

ifeq ($(TIMER0),1)
$(eval $(call add_define,TIMER0))
include $(HAL_DIR)/timer/build.mk
endif

ifeq ($(UART0),1)
$(eval $(call add_define,UART0))
include $(HAL_DIR)/uart/build.mk
endif

ifeq ($(WDT0),1)
$(eval $(call add_define,WDT0))
include $(HAL_DIR)/wdt/build.mk
endif
