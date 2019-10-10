HAL_DIR	:= $(GET_PATH)

include $(HAL_DIR)/clkctl/build.mk
include $(HAL_DIR)/gpio/build.mk
ifeq ($(ADC),1)
include $(HAL_DIR)/adc/build.mk
endif
include $(HAL_DIR)/eeprom/build.mk
include $(HAL_DIR)/i2c/build.mk
include $(HAL_DIR)/int/build.mk
include $(HAL_DIR)/pcint/build.mk
include $(HAL_DIR)/spi/build.mk
include $(HAL_DIR)/timer/build.mk
include $(HAL_DIR)/uart/build.mk
include $(HAL_DIR)/wdt/build.mk
