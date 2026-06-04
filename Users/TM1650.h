#ifndef _TM1650_H
#define _TM1650_H

#include "stm8s.h"

#define I2C_PORT    GPIOC
#define I2C_SCL_Pin GPIO_PIN_5
#define I2C_SDA_Pin GPIO_PIN_6

//控制命令，显示设置，一个字节
//1Byte：B7：X，B6B5B4：亮度等级，B3：8段显示0，7段显示1，B2B1：XX，B0：关显示0，开显示1
#define CONTROL_CMD  0x48
#define SCANKEY_CMD  0x49

//开显示，1级亮度，8段显示
#define DISPLAY_ON  0x11
#define DISPLAY_OFF 0x10

//显存地址
#define DATA_ADDR1 0x68
#define DATA_ADDR2 0x6A
#define DATA_ADDR3 0x6C
#define DATA_ADDR4 0x6E

#define I2C_SCL_L GPIO_WriteLow(I2C_PORT,I2C_SCL_Pin) 
#define I2C_SCL_H GPIO_WriteHigh(I2C_PORT,I2C_SCL_Pin) 

#define I2C_SDA_L GPIO_WriteLow(I2C_PORT,I2C_SDA_Pin) 
#define I2C_SDA_H GPIO_WriteHigh(I2C_PORT,I2C_SDA_Pin) 

void TM1650_Init(void);
uint8_t TM1650_ReadKey(void);
void TM1650_Set(uint8_t addr,uint8_t data);
void TM1650_DisplaySet(uint8_t cmd);
void TM1650_Show_Number(u16 num);

#endif /* __TM1650_H__ */
