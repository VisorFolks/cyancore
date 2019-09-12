PERIPHERALS_DIR	:= $(GET_PATH)

include $(PERIPHERALS_DIR)/clkctl/build.mk
include $(PERIPHERALS_DIR)/gpio/build.mk
include $(PERIPHERALS_DIR)/adc/build.mk
include $(PERIPHERALS_DIR)/eeprom/build.mk
include $(PERIPHERALS_DIR)/i2c/build.mk
include $(PERIPHERALS_DIR)/int/build.mk
include $(PERIPHERALS_DIR)/pcint/build.mk
include $(PERIPHERALS_DIR)/spi/build.mk
include $(PERIPHERALS_DIR)/timer/build.mk
include $(PERIPHERALS_DIR)/uart/build.mk
include $(PERIPHERALS_DIR)/wdt/build.mk
