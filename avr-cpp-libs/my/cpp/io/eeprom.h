#ifndef __AVR_CPP_IO_H_EEPROM__
#define __AVR_CPP_IO_H_EEPROM__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif

union EepromControl
{
	struct
	{
		volatile uint8_t	readEnable			:1;
		volatile uint8_t	writeEnable			:1;
		volatile uint8_t	masterWriteEnable	:1;
		volatile uint8_t	interruptEnable		:1;
		volatile uint8_t						:4;
	};
	struct
	{
		uint8_t	readEnable_			:1;
		uint8_t	writeEnable_		:1;
		uint8_t	masterWriteEnable_	:1;
		uint8_t	interruptEnable_	:1;
		uint8_t						:4;
	};
};


#endif // ifndef __AVR_CPP_IO_H_EEPROM__

