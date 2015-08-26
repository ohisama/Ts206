#include "Ts206.h"

#define TAKE_CS()			digitalWrite(cs_pin, LOW)
#define RELEASE_CS() 		digitalWrite(cs_pin, HIGH)
#define COMMAND_MODE 		0b100
#define WRITE_MODE 			0b101

void Ts206::writeBits(uint8_t data, uint8_t cnt)
{
	uint8_t bitmask;
	while (cnt)
	{
		digitalWrite(wr_pin, LOW);
		uint8_t bitval = (data & (1 << (cnt - 1))) ? HIGH : LOW;
		digitalWrite(data_pin, bitval);
		digitalWrite(wr_pin, HIGH);
		cnt--;
	}
}
void Ts206::sendCommand(uint8_t cmd, bool first, bool last)
{
	if (first)
	{
		TAKE_CS();
		writeBits(COMMAND_MODE, 3);
	}
	writeBits(cmd, 8);
	writeBits(0, 1);
	if (last) RELEASE_CS();
}
void Ts206::writeMem(uint8_t address, uint8_t data)
{
	TAKE_CS();
	writeBits(WRITE_MODE, 3);
	writeBits(address, 6);
	writeBits(data, 4);
	RELEASE_CS();
}
void Ts206::memset(uint8_t address, uint8_t data, uint8_t cnt)
{
	TAKE_CS();
	writeBits(WRITE_MODE, 3);
	writeBits(address, 6);
	for (uint8_t i = 0; i < cnt; i++) writeBits(data, 4);
	RELEASE_CS();
}
void Ts206::write(uint8_t address, uint8_t * data, uint8_t cnt)
{
	TAKE_CS();
	writeBits(WRITE_MODE, 3);
	writeBits(address, 6);
	for (uint8_t i = 0; i < cnt; i++) writeBits(data[i], 4);
	RELEASE_CS();
}
void Ts206::initControlBus(void)
{
	pinMode(data_pin, OUTPUT);
	pinMode(wr_pin, OUTPUT);
	pinMode(cs_pin, OUTPUT);
	digitalWrite(cs_pin, HIGH);
	digitalWrite(wr_pin, HIGH);
	digitalWrite(data_pin, HIGH);
}
void Ts206::begin(void)
{
	initControlBus();
	sendCommand(SYS_EN);
	sendCommand(BIAS_THIRD_4_COM);
	sendCommand(LCD_ON);
}
void Ts206::disp(uint8_t address, uint8_t data)
{
	uint8_t font[] = {
0b00000000,
0b11010000,
0b00010010,
0b01111110,
0b01101011,
0b00000000,
0b00000000,
0b00010000,
0b00000110,
0b01010000,
0b00110011,
0b00000000,
0b01000000,
0b00100000,
0b10000000,
0b00110100,
0b01011111,
0b01010000,
0b00111101,
0b01111001,
0b01110010,
0b01101011,
0b01101111,
0b01010011,
0b01111111,
0b01111011,
0b00000000,
0b00000000,
0b00000000,
0b00101000,
0b00000000,
0b00110101,
0b01111101,
0b01110111,
0b01111111,
0b00001111,
0b01011111,
0b00101111,
0b00100111,
0b01001111,
0b01110110,
0b01010000,
0b01011101,
0b00101011,
0b00001110,
0b01000101,
0b01010111,
0b01011111,
0b00110111,
0b01110011,
0b00000111,
0b01101011,
0b00101110,
0b01011110,
0b00011010,
0b01001101,
0b01110110,
0b01111010,
0b00111101,
0b00001111,
0b01100010,
0b01011001,
0b00000000,
0b00001000,
0b00000010,
0b01111101,
0b01101110,
0b00101100,
0b01111100,
0b00111111,
0b00000111,
0b01111011,
0b01100110,
0b01000000,
0b01011000,
0b01100111,
0b00000110,
0b01100101,
0b01100100,
0b01101100,
0b00110111,
0b01110011,
0b00100100,
0b01101011,
0b00101110,
0b01001100,
0b00011010,
0b01001101,
0b01110110,
0b01111010,
0b01110001,
0b01110000,
0b01010000,
0b00100110,
0b00000001,

	};
	uint8_t d = font[data - 32];
	uint8_t a = address * 2 + 4;
	uint8_t e = d & 0x0f;
	writeMem(a, e);
	d = d >> 4;
	a = a + 1;
	writeMem(a, d);
}
