#ifndef __SD3077_H__
#define __SD3077_H__

#include "stm32f0xx_hal.h"
#include "i2c.h"

#define SD3077_IIC_HANDLE     hi2c1
#define SD3077_IIC_ADDR_READ  (uint8_t)0x65
#define SD3077_IIC_ADDR_WRITE (uint8_t)0x64

typedef enum {
	AM = 0x00,
	PM = 0x01,
	HOUR24 = 0x02
} AM_PM;

typedef struct{
	uint8_t seconds;
	uint8_t minutes;
	AM_PM   ampm;
	uint8_t hours;
	uint8_t dayOfWeek;
	uint8_t dayOfMonth;
	uint8_t month;
	uint8_t year;
} DateTime;

/**
 * SD3077的中断输出频率定义，为0即关闭中断输出
 */
typedef enum{
	F_0_HZ       = 0x00,
	F_4096_HZ    = 0x02,
	F_1024_HZ    = 0x03,
	F_64_HZ      = 0x04,
	F_32_HZ      = 0x05,
	F_16_HZ      = 0x06,
	F_8_HZ       = 0x07,
	F_4_HZ       = 0x08,
	F_2_HZ       = 0x09,
	F_1_HZ       = 0x0A,
	F_0_5_HZ     = 0x0B,
	F_0_25_HZ    = 0x0C,
	F_0_125_HZ   = 0x0D,
	F_0_0625_HZ  = 0x0E,
	F_1_S        = 0x0F,
} SD3077IntFreq;

void TimeNow(DateTime *dateTime);
void SetTime(DateTime *dateTime);
void SetInterruptOuput(SD3077IntFreq freq);
void EnableSencodInterruptOuput();
void WriteBackData(uint8_t index, uint8_t *data, uint8_t size);
void ReadBackData(uint8_t index, uint8_t *data, uint8_t size);

#endif
