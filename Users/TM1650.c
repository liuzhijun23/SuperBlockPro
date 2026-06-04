#include "TM1650.h"

// 0~9显示代码
uint8_t SEG_CODE[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void Delay_us(uint32_t us)
{
    for (uint32_t i = 0; i < us; i++)
    {
        for (uint32_t j = 0; j < 16; j++)
            ;
    }
}

void I2C_Start(void)
{
    I2C_SDA_H;
    I2C_SCL_H;
    Delay_us(2);
    I2C_SDA_L;
    Delay_us(2);
    I2C_SCL_L;
}

void I2C_Stop(void)
{
    I2C_SCL_L;
    I2C_SDA_L;
    Delay_us(2);
    I2C_SCL_H;
    Delay_us(2);
    I2C_SDA_H;
    Delay_us(2);
}

void I2C_Ack(void)
{
    I2C_SCL_L;
    I2C_SDA_L;
    Delay_us(2);
    I2C_SCL_H;
    Delay_us(5);
    I2C_SCL_L;
}

void I2C_NAck(void)
{
    I2C_SCL_L;
    I2C_SDA_H;
    Delay_us(2);
    I2C_SCL_H;
    Delay_us(5);
    I2C_SCL_L;
}

// 返回1 代表非应答信号
// 返回0 代表有应答信号
uint8_t I2C_Wait_Ack(void)
{
    uint16_t timeOut = 0;

    Delay_us(2);
    I2C_SCL_H;
    Delay_us(5);

    while (GPIO_ReadInputPin(I2C_PORT, I2C_SDA_Pin))
    {
        timeOut++;
        if (timeOut > 1000)
        {
            I2C_Stop();
            return 1;
        }
    }

    I2C_SCL_L;

    return 0;
}

void I2C_Send_Byte(uint8_t txd)
{
    I2C_SCL_L;

    for (uint8_t i = 0; i < 8; i++)
    {
        if ((txd & 0x80) > 0)
        {
            I2C_SDA_H;
        }
        else
        {
            I2C_SDA_L;
        }

        txd <<= 1;
        I2C_SCL_H;
        Delay_us(2);
        I2C_SCL_L;
        Delay_us(2);
    }
}
// ack=0 发送非应答信号，代表接收完成
// ack=1 发送应答信号，代表接收未完成，继续接收
uint8_t I2C_Read_Byte(uint8_t ack)
{
    uint8_t receive = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        I2C_SCL_L;
        Delay_us(2);
        I2C_SCL_H;
        Delay_us(2);

        receive <<= 1;

        if (GPIO_ReadInputPin(I2C_PORT, I2C_SDA_Pin))
        {
            receive |= 1;
        }

        Delay_us(1);
    }

    if (ack == 0)
    {
        I2C_NAck();
    }
    else
    {
        I2C_Ack();
    }

    return receive;
}

void TM1650_Set(uint8_t addr, uint8_t data)
{
    I2C_Start();

    I2C_Send_Byte(addr);
    I2C_Wait_Ack();

    I2C_Send_Byte(data);
    I2C_Wait_Ack();

    I2C_Stop();
}

uint8_t TM1650_ReadKey(void)
{
    uint8_t key = 0;

    I2C_Start();
    I2C_Send_Byte(SCANKEY_CMD);
    I2C_Wait_Ack();

    key = I2C_Read_Byte(0);
    I2C_Stop();

    return key;
}

// 8级亮度设置，7/8段显示，开关显示位
void TM1650_DisplaySet(uint8_t cmd)
{
    TM1650_Set(CONTROL_CMD, cmd);
}

void TM1650_Init(void)
{
    GPIO_Init(GPIOC, I2C_SCL_Pin, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOC, I2C_SDA_Pin, GPIO_MODE_OUT_PP_HIGH_FAST);

    //开显示，1级亮度，8段显示
    TM1650_DisplaySet(DISPLAY_ON);
}

void TM1650_Show_Number(u16 num)
{
    //TM1650_Init();
    u8 digit1 = num%10;
    num = num/10;
    u8 digit2 = num%10;
    num = num/10;
    u8 digit3 = num%10;
    TM1650_Set(DATA_ADDR1, SEG_CODE[digit3]); //带小数点
    TM1650_Set(DATA_ADDR2, SEG_CODE[digit2]);
    TM1650_Set(DATA_ADDR3, SEG_CODE[digit1]);
}
