/*
	Works correct with frequency <= 32 MHz	
*/
#ifndef _TM1637_H_
#define _TM1637_H_

#include "stm32f0xx_hal.h"

#define TM1637_SCLK_PORT GPIOF
#define TM1637_SCLK_PIN  GPIO_PIN_0

#define TM1637_SDIO_PORT GPIOF
#define TM1637_SDIO_PIN  GPIO_PIN_1

#define TM1637_DP_0  0x01
#define TM1637_DP_1  0x02
#define TM1637_DP_2  0x04
#define TM1637_DP_3  0x08
#define TM1637_DP_4  0x10
#define TM1637_DP_5  0x20

void TM1637Init(void);

/**
 * 显示一个数字，显示方式为左对齐。这个数字不能大于6位，大于6位的部分不会显示。
 * 非指定位置内容不会保留。
 * index：显示位置
 * num：要显示的数字
 * pointLocation：显示小数点的位置，计数方式为从右到左。
 */
void TM1637ShowNumberLeft(uint8_t index, uint32_t num, uint8_t pointLocation);

/**
 * 显示一个数字，显示方式为右对齐。这个数字不能大于6位，大于6位的部分不会显示。
 * 非指定位置内容不会保留。
 * index：显示位置
 * num：要显示的数字
 * pointLocation：显示小数点的位置，计数方式为从右到左。
 */
void TM1637ShowNumberRight(uint8_t index, uint32_t num, uint8_t pointLocation, uint8_t isPaddingZero);

/**
 * 在指定位置显示一个字符。不支持的字符不会显示.
 * 非指定位置的字符会保留。
 * index：显示位置
 * c：字符
 * point：是否显示小数点
 */
void TM1637SetChar(uint8_t index, char c, uint8_t point);

/**
 * 在指定位置显示指定的数据
 */
void TM1637SetRawData(uint8_t index, uint8_t data);

/**
 * 设置亮度，范围0~8，0为关闭，8为全亮
 */
void TM1637SetBrightness(uint8_t brightness);

#endif
