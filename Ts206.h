#ifndef Ts206_H
#define Ts206_H
#include <Arduino.h>

class Ts206
{
public:
	enum {
		SYS_DIS = 			0b00000000,
		SYS_EN =  			0b00000001,
		LCD_OFF = 			0b00000010,
		LCD_ON =  			0b00000011,
		TIMER_DIS = 		0b00000100,
		WDT_DIS = 			0b00000101,
		TIMER_EN = 			0b00000110,
		WDT_EN = 			0b00000111,
		TONE_OFF = 			0b00001000,
		TONE_ON = 			0b00001001,
		BIAS_HALF_2_COM = 	0b00100000,
		BIAS_HALF_3_COM = 	0b00100100,
		BIAS_HALF_4_COM = 	0b00101000,
		BIAS_THIRD_2_COM = 	0b00100001,
		BIAS_THIRD_3_COM = 	0b00100101,
		BIAS_THIRD_4_COM = 	0b00101001,
	} Commands;
 	Ts206(uint8_t data, uint8_t wr, uint8_t cs) : data_pin(data), wr_pin(wr), cs_pin(cs)
	{
	};
 	void begin(void);
 	void sendCommand(uint8_t cmd, bool first = true, bool last = true);
 	void write(uint8_t address, uint8_t * data, uint8_t cnt);
 	void writeMem(uint8_t address, uint8_t data);
 	void memset(uint8_t address, uint8_t data, uint8_t cnt);
	void disp(uint8_t address, uint8_t data);
private:
	void writeBits(uint8_t data, uint8_t cnt);
 	void initControlBus(void);
	uint8_t data_pin;
	uint8_t wr_pin;
	uint8_t cs_pin;
};
#endif
