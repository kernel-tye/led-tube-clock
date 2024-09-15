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
 * ��ʾһ�����֣���ʾ��ʽΪ����롣������ֲ��ܴ���6λ������6λ�Ĳ��ֲ�����ʾ��
 * ��ָ��λ�����ݲ��ᱣ����
 * index����ʾλ��
 * num��Ҫ��ʾ������
 * pointLocation����ʾС�����λ�ã�������ʽΪ���ҵ���
 */
void TM1637ShowNumberLeft(uint8_t index, uint32_t num, uint8_t pointLocation);

/**
 * ��ʾһ�����֣���ʾ��ʽΪ�Ҷ��롣������ֲ��ܴ���6λ������6λ�Ĳ��ֲ�����ʾ��
 * ��ָ��λ�����ݲ��ᱣ����
 * index����ʾλ��
 * num��Ҫ��ʾ������
 * pointLocation����ʾС�����λ�ã�������ʽΪ���ҵ���
 */
void TM1637ShowNumberRight(uint8_t index, uint32_t num, uint8_t pointLocation, uint8_t isPaddingZero);

/**
 * ��ָ��λ����ʾһ���ַ�����֧�ֵ��ַ�������ʾ.
 * ��ָ��λ�õ��ַ��ᱣ����
 * index����ʾλ��
 * c���ַ�
 * point���Ƿ���ʾС����
 */
void TM1637SetChar(uint8_t index, char c, uint8_t point);

/**
 * ��ָ��λ����ʾָ��������
 */
void TM1637SetRawData(uint8_t index, uint8_t data);

/**
 * �������ȣ���Χ0~8��0Ϊ�رգ�8Ϊȫ��
 */
void TM1637SetBrightness(uint8_t brightness);

#endif
