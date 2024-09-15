#include "SD3077.h"

static uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4); }
static uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10); }

static void UnlockWriteProtect(){
	// 读出控制寄存器中的数据
	uint8_t srcData[2];
	HAL_I2C_Mem_Read(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_READ, 0x0F, 1, srcData, 2, HAL_MAX_DELAY);

	// 更改后写入
	uint8_t data = srcData[1] | 0x80;
	HAL_I2C_Mem_Write(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_WRITE, 0x10, 1, &data, 1, HAL_MAX_DELAY);
	data = srcData[0] | 0x04;
	HAL_I2C_Mem_Write(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_WRITE, 0x0F, 1, &data, 1, HAL_MAX_DELAY);
	data = srcData[0] | 0x84;
	HAL_I2C_Mem_Write(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_WRITE, 0x0F, 1, &data, 1, HAL_MAX_DELAY);
}

void TimeNow(DateTime *dateTime){
	uint8_t data[7];
	HAL_I2C_Mem_Read(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_READ, 0x00, 1, data, 7, HAL_MAX_DELAY);
	dateTime->seconds = bcd2bin(data[0]);
	dateTime->minutes = bcd2bin(data[1]);

	if(data[2] >> 7){
		dateTime->ampm = HOUR24;
		dateTime->hours = bcd2bin(data[2] & 0x7F);
	}
	else{
		dateTime->ampm =  (data[2] & 0x20) >> 5;
		dateTime->hours = bcd2bin(data[2] & 0x1F);
	}

	dateTime->dayOfWeek = bcd2bin(data[3]);
	dateTime->dayOfMonth = bcd2bin(data[4]);
	dateTime->month = bcd2bin(data[5]);
	dateTime->year = bcd2bin(data[6]);
}

void SetTime(DateTime *dateTime){
	// 解除写保护
	UnlockWriteProtect();

	uint8_t data[7];
	data[0] = bin2bcd(dateTime->seconds);
	data[1] = bin2bcd(dateTime->minutes);
	data[2] = bin2bcd(dateTime->hours);
	data[3] = bin2bcd(dateTime->dayOfWeek);
	data[4] = bin2bcd(dateTime->dayOfMonth);
	data[5] = bin2bcd(dateTime->month);
	data[6] = bin2bcd(dateTime->year);

	if((dateTime -> ampm) == HOUR24){
		data[2] |= 0x80;
	}
	else{
		data[2] |= (dateTime -> ampm) << 5;
	}

	HAL_I2C_Mem_Write(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_WRITE, 0x00, 1, data, 7, HAL_MAX_DELAY);
}

void EnableSencodInterruptOuput(){
	// 解除写保护
	UnlockWriteProtect();

	// 读出控制寄存器2和3
	uint8_t data[2];
	HAL_I2C_Mem_Read(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_READ, 0x10, 1, data, 2, HAL_MAX_DELAY);

	// 允许频率中断
	data[0] |= 0x01;
	// 选择频率中断输出
	data[0] |= 0x20;
	data[0] &= 0xEF;

	// 设置频率为1Hz
//	data[1] &= 0xF0;
//	data[1] |= 0x0A;

	// 设置频率为1秒
	data[1] |= 0x0F;

	// 控制寄存器回写
	HAL_I2C_Mem_Write(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_WRITE, 0x10, 1, data, 2, HAL_MAX_DELAY);
}

void SetInterruptOuput(SD3077IntFreq freq){
	// 解除写保护
	UnlockWriteProtect();

	// 读出控制寄存器2和3
	uint8_t data[2];
	HAL_I2C_Mem_Read(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_READ, 0x10, 1, data, 2, HAL_MAX_DELAY);

	// 允许频率中断
	data[0] |= 0x01;
	// 选择频率中断输出
	data[0] |= 0x20;
	data[0] &= 0xEF;

	// 设置频率为1Hz
	data[1] &= 0xF0;
	data[1] |= freq;

	// 设置频率为1秒
//	data[1] |= 0x0F;

	// 控制寄存器回写
	HAL_I2C_Mem_Write(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_WRITE, 0x10, 1, data, 2, HAL_MAX_DELAY);
}

void WriteBackData(uint8_t index, uint8_t *data, uint8_t size){
	if(index > 69) return;

	// 解除写保护
	UnlockWriteProtect();

	// 写入备份寄存器
	HAL_I2C_Mem_Write(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_WRITE, 0x2C + index, 1, data, size, HAL_MAX_DELAY);
}

void ReadBackData(uint8_t index, uint8_t *data, uint8_t size){
	if(index > 69) return;

	// 从备份寄存器读出
	HAL_I2C_Mem_Read(&SD3077_IIC_HANDLE, SD3077_IIC_ADDR_READ, 0x2C + index, 1, data, size, HAL_MAX_DELAY);
}
