#include "TM1637.h"

#define SCLK_Set() (TM1637_SCLK_PORT->BSRR = TM1637_SCLK_PIN)
#define SCLK_Reset()  (TM1637_SCLK_PORT->BRR = TM1637_SCLK_PIN)
#define SDIO_Set() (TM1637_SDIO_PORT->BSRR = TM1637_SDIO_PIN)
#define SDIO_Reset()  (TM1637_SDIO_PORT->BRR = TM1637_SDIO_PIN)

#ifndef GPIO_ResetPin
#define GPIO_ResetPin(GPIOx, PIN) (GPIOx -> BRR = PIN);
#endif
#ifndef GPIO_SetPin
#define GPIO_SetPin(GPIOx, PIN)   (GPIOx -> BSRR = PIN);
#endif


static void start(void);
static void stop(void);
static void waitACK(void);
static void WriteByte(uint8_t b);
static void delay(uint32_t i);
static uint8_t translateFromChar(char c);

const uint8_t numbersMap[] = {
    0x3f, // 0d
	0x06, // 1d
	0x5b, // 2d
	0x4f, // 3d
	0x66, // 4d 
	0x6d, // 5d
	0x7d, // 6d
	0x07, // 7d
    0x7f, // 8d
	0x6f, // 9d
};


uint32_t power(uint32_t x, uint8_t n) {
	uint32_t rst = 1;
	while (n--) {
		rst *= x;
	}
	return rst;
}

void TM1637Init(void)
{
    TM1637SetBrightness(8);
}

void TM1637SetBrightness(uint8_t brightness)
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-7
    // X = don't care
    // B = brightness
    start();
    WriteByte(0x87 + brightness);
    waitACK();
    stop();

}

void TM1637ShowNumberLeft(uint8_t index, uint32_t num, uint8_t pointLocation) {

	uint8_t size = 6 - index;
	uint8_t n = 6;
	do {
		uint32_t dig = num / power(10, n - 1);
		if (dig != 0) {
			break;
		}
	} while (--n);

	size = n > size ? size : n;

	uint8_t digits[6];
	for (uint8_t i = 0; i < size; i++) {
		digits[i] = numbersMap[num % 10];
		if (pointLocation == i) {
			digits[i] |= 0x80;
		}
		num /= 10;
	}

	start();
	WriteByte(0x40);
	waitACK();
	stop();

	start();
	WriteByte(0xc0 + index);
	waitACK();

	for (uint8_t i = 0; i < 6; ++i) {
		WriteByte(digits[size - 1 - i]);
		waitACK();
	}

	stop();
}

void TM1637ShowNumberRight(uint8_t index, uint32_t num, uint8_t pointLocation, uint8_t isPaddingZero) {

	uint8_t n = 6;
	do {
		uint32_t dig = num / power(10, n - 1);
		if (dig != 0) {
			break;
		}
	} while (--n);

	uint8_t digits[6];
	for (uint8_t i = 0; i < 6; i++) {
		if(i < n || isPaddingZero){
			digits[i] = numbersMap[num % 10];
		}
		else{
			digits[i] = 0;
		}

		if (pointLocation == i) {
			digits[i] |= 0x80;
		}
		num /= 10;
	}

	start();
	WriteByte(0x40);
	waitACK();
	stop();

	start();
	WriteByte(0xc0);
	waitACK();

	for (uint8_t i = 0; i < 6; ++i) {
		if(i <= index){
			WriteByte(digits[index - i]);
		}
		else{
			WriteByte(0);
		}

		waitACK();
	}

	stop();
}

void TM1637SetChar(uint8_t index, char c, uint8_t point){
	TM1637SetRawData(index, translateFromChar(c)| (point?0x80:0x00));
}

void TM1637SetRawData(uint8_t index, uint8_t data){
	start();
	WriteByte(0x44); // 固定地址模式
	waitACK();
	stop();

	start();
	WriteByte(0xC0 + index); // 固定地址模式
	waitACK();
	WriteByte(data);
	waitACK();
	stop();
}

void start(void)
{
    SCLK_Set();
    SDIO_Set();
    delay(2);
    SDIO_Reset();
}

void stop(void)
{
    SCLK_Reset();
    delay(2);
    SDIO_Reset();
    delay(2);
    SCLK_Set();
    delay(2);
    SDIO_Set();
}

void waitACK(void)
{
    SCLK_Reset();
    delay(5);
    SCLK_Set();
    delay(2);
    SCLK_Reset();
}

void WriteByte(uint8_t b)
 {
	for (uint8_t i = 0; i < 8; ++i) {
		SCLK_Reset();
		if (b & 0x01) {
			SDIO_Set();
		}
		else {
			SDIO_Reset();
		}
		delay(3);
		b >>= 1;
		SCLK_Set();
		delay(3);
	}
}
	
void delay(uint32_t i)
 {
	for (; i > 0; i--) {
		for (int j = 0; j < 10; ++j) {
			asm("nop");
		}
	}
}


static uint8_t translateFromChar(char c){
	switch(c){
		case '0': return 0x3F;
		case '1': return 0x06;
		case '2': return 0x5B;
		case '3': return 0x4F;
		case '4': return 0x66;
		case '5': return 0x6D;
		case '6': return 0x7D;
		case '7': return 0x07;
		case '8': return 0x7F;
		case '9': return 0x6F;
		case 'a': case 'A':return 0x77;
		case 'b': case 'B': return 0x7C;
		case 'c': return 0x58;
		case 'C': return 0x39;
		case 'd': case 'D': return 0x5E;
		case 'e': case 'E':return 0x79;
		case 'f': case 'F': return 0x71;
		case 'H': return 0x76;
		case 'h': return 0x74;
		case 'i': return 0x10;
		case 'I': return 0x30;
		case 'j': case 'J': return 0x1E;
		case 'l': case 'L': return 0x38;
		case 'N': case 'n': return 0x54;
		case 'o': case 'O': return 0x5C;
		case 'p': case 'P': return 0x73;
		case 'r': case 'R': return 0x50;
		case 's': case 'S': return 0x6D;
		case 'T': case 't': return 0x44;
		case 'u': return 0x1C;
		case 'U': return 0x3E;
		case '-': return 0x40;
		case '_': return 0x08;
		default: return 0x00;
	}
}
