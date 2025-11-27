//
// Created by 陈浩瑜 on 25-11-19.
//
#include "tlc5615.h"
#define TLC5615_index_Max 90
const uint16_t sine_table[] = {
    91,97,103,109,114,120,125,130,135,140,144,149,152,156,159,162,164,
    166,168,169,170,170,170,169,168,167,165,163,161,158,154,151,147,142,138,
    133,128,123,117,111,106,100,94,88,82,76,70,64,58,52,47,42,37,32,27,23,19,15,12,
    9,6,4,2,1,0,0,0,0,1,2,3,5,8,10,14,17,21,25,29,34,39,44,50,55,61,67,73,79,85,91
};
const uint16_t square_table[90]={
    170,170,170,170,170,170,170,170,170,170,
    170,170,170,170,170,170,170,170,170,170,
    170,170,170,170,170,170,170,170,170,170,
    170,170,170,170,170,170,170,170,170,170,
    170,170,170,170,170,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0
};
const uint16_t triangle_table[90]={
    0,3,7,11,15,19,23,27,31,34,38,42,46,50,54,58,62,65,69,73,77,81,85,89,93,96,100,104,108,112,116,120,124,127,131,135,139,143,147,151,155,158,162,166,170,170,166,162,158,155,151,147,143,139,135,131,127,124,120,116,112,108,104,100,96,93,89,85,81,77,73,69,65,62,58,54,50,46,42,38,34,31,27,23,19,15,11,7,3,0};

};
// 私有函数声明
static void TLC5615_Delay_us(uint32_t us);
static TLC5615_StatusTypeDef TLC5615_HardwareSPI_Write(TLC5615_HandleTypeDef *htlc5615, uint16_t data);

// 微秒延时函数
static void TLC5615_Delay_us(uint32_t us)
{
    uint32_t ticks = us * (SystemCoreClock / 1000000) / 10;
    while (ticks--)
        ;
}

// // 硬件SPI写入函数
// static TLC5615_StatusTypeDef TLC5615_HardwareSPI_Write(TLC5615_HandleTypeDef *htlc5615, uint16_t data)
// {
//     uint8_t tx_data[2];
//     HAL_StatusTypeDef status;
//
//     // 转换为大端格式
//     tx_data[0] = (data >> 8) & 0xFF;
//     tx_data[1] = data & 0xFF;
//
//     // 片选使能
//     HAL_GPIO_WritePin(htlc5615->cs_port, htlc5615->cs_pin, GPIO_PIN_RESET);
//     TLC5615_Delay_us(1);
//
//     // SPI传输
//     status = HAL_SPI_Transmit(htlc5615->hspi, tx_data, 2, htlc5615->timeout);
//
//     // 片选禁用
//     HAL_GPIO_WritePin(htlc5615->cs_port, htlc5615->cs_pin, GPIO_PIN_SET);
//
//     if (status != HAL_OK)
//     {
//         return TLC5615_ERROR;
//     }
//
//     return TLC5615_OK;
// }

// 初始化函数
TLC5615_StatusTypeDef TLC5615_Init(TLC5615_HandleTypeDef *htlc5615)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (htlc5615 == NULL)
    {
        return TLC5615_ERROR;
    }

    // 配置CS引脚
    GPIO_InitStruct.Pin = htlc5615->cs_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(htlc5615->cs_port, &GPIO_InitStruct);

    // 初始状态：CS高电平
    HAL_GPIO_WritePin(htlc5615->cs_port, htlc5615->cs_pin, GPIO_PIN_SET);

    // 设置默认超时时间
    if (htlc5615->timeout == 0)
    {
        htlc5615->timeout = 100;
    }

    return TLC5615_OK;
}

// 写入10位数字值
TLC5615_StatusTypeDef TLC5615_WriteValue(TLC5615_HandleTypeDef *htlc5615, uint16_t value)
{
    uint16_t send_data;
    TLC5615_StatusTypeDef status;

    if (htlc5615 == NULL)
    {
        return TLC5615_ERROR;
    }

    // 限制输入范围
    if (value > 1023)
    {
        value = 1023;
    }

    // 将10位数据转换为12位格式并左移4位形成16位数据包
    // 格式：0000 D9 D8 D7 D6 D5 D4 D3 D2 D1 D0 00
    //send_data = (value << 2) & 0x0FFC;
    value<<=6;
    HAL_GPIO_WritePin(htlc5615->cs_port, htlc5615->cs_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(htlc5615->sclk_port, htlc5615->sclk_pin, GPIO_PIN_RESET);
    for(uint8_t i= 0; i < 12; i++)
    {
        if(value&0x8000)
        {
            HAL_GPIO_WritePin(htlc5615->din_port, htlc5615->din_pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(htlc5615->din_port, htlc5615->din_pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(htlc5615->sclk_port, htlc5615->sclk_pin, GPIO_PIN_SET);
        value<<=1;
        HAL_GPIO_WritePin(htlc5615->sclk_port, htlc5615->sclk_pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(htlc5615->cs_port, htlc5615->cs_pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(htlc5615->sclk_port, htlc5615->sclk_pin, GPIO_PIN_RESET);


    // status = TLC5615_HardwareSPI_Write(htlc5615, send_data);
    ;


    if (status == TLC5615_OK)
    {
        // 等待建立时间（典型值12.5us）
        TLC5615_Delay_us(15);
    }

    return status;
}

void TLC5615_OutSignal(TLC5615_HandleTypeDef *htlc5615, uint16_t *value_table,uint8_t beishu) {
    static uint32_t tickstart = 0;
    static uint16_t index = 0;

    if(HAL_GetTick() - tickstart >= 10)
    {
        uint16_t dac_value = value_table[index]*beishu;
        TLC5615_WriteValue(&htlc5615, dac_value);

        index++;
        if(index >= TLC5615_index_Max)
        {
            index = 0;
        }

        tickstart = HAL_GetTick();
    }
}

// 写入电压值
TLC5615_StatusTypeDef TLC5615_WriteVoltage(TLC5615_HandleTypeDef *htlc5615, float voltage)
{
    uint16_t digital_value;
    float max_voltage;

    if (htlc5615 == NULL)
    {
        return TLC5615_ERROR;
    }

    max_voltage = 2.0f * htlc5615->ref_voltage;

    // 限制电压范围
    if (voltage < 0)
        voltage = 0;
    if (voltage > max_voltage)
        voltage = max_voltage;

    // 计算数字值
    digital_value = (uint16_t)((voltage / max_voltage) * 1023.0f);

    return TLC5615_WriteValue(htlc5615, digital_value);
}

// 设置参考电压
TLC5615_StatusTypeDef TLC5615_SetReferenceVoltage(TLC5615_HandleTypeDef *htlc5615, float ref_voltage)
{
    if (htlc5615 == NULL)
    {
        return TLC5615_ERROR;
    }

    htlc5615->ref_voltage = ref_voltage;
    return TLC5615_OK;
}

// 根据数字值计算输出电压
float TLC5615_GetOutputVoltage(TLC5615_HandleTypeDef *htlc5615, uint16_t digital_value)
{
    if (htlc5615 == NULL || digital_value > 1023)
    {
        return 0.0f;
    }

    return (2.0f * htlc5615->ref_voltage * digital_value) / 1023.0f;
}

// 低功耗模式
TLC5615_StatusTypeDef TLC5615_PowerDown(TLC5615_HandleTypeDef *htlc5615)
{
    return TLC5615_WriteValue(htlc5615, 0);
}

// 唤醒芯片
TLC5615_StatusTypeDef TLC5615_WakeUp(TLC5615_HandleTypeDef *htlc5615)
{
    return TLC5615_WriteValue(htlc5615, 512);
}

// 多设备级联写入
TLC5615_StatusTypeDef TLC5615_DaisyChainWrite(TLC5615_HandleTypeDef *htlc5615, uint16_t *values, uint8_t device_count)
{
    uint8_t i;

    if (htlc5615 == NULL || values == NULL || device_count == 0 || device_count > 8)
    {
        return TLC5615_ERROR;
    }

    for (i = 0; i < device_count; i++)
    {
        if (TLC5615_WriteValue(htlc5615, values[i]) != TLC5615_OK)
        {
            return TLC5615_ERROR;
        }
        HAL_Delay(1); // 设备间延时
    }

    return TLC5615_OK;
}

// 波形生成功能
TLC5615_StatusTypeDef TLC5615_GenerateWaveform(TLC5615_HandleTypeDef *htlc5615, TLC5615_WaveformConfigTypeDef *config)
{
    uint16_t value;

    if (htlc5615 == NULL || config == NULL)
    {
        return TLC5615_ERROR;
    }

    // 生成三角波
    for (value = config->min_value; value <= config->max_value; value += config->step)
    {
        if (TLC5615_WriteValue(htlc5615, value) != TLC5615_OK)
        {
            return TLC5615_ERROR;
        }
        HAL_Delay(config->delay_ms);
    }

    for (value = config->max_value; value >= config->min_value; value -= config->step)
    {
        if (TLC5615_WriteValue(htlc5615, value) != TLC5615_OK)
        {
            return TLC5615_ERROR;
        }
        HAL_Delay(config->delay_ms);
    }

    return TLC5615_OK;
}

// 反初始化
TLC5615_StatusTypeDef TLC5615_DeInit(TLC5615_HandleTypeDef *htlc5615)
{
    if (htlc5615 == NULL)
    {
        return TLC5615_ERROR;
    }

    // 重置引脚
    HAL_GPIO_WritePin(htlc5615->cs_port, htlc5615->cs_pin, GPIO_PIN_SET);

    return TLC5615_OK;
}

// 预计算的正弦波表（32个点，精度更高）
static const uint16_t sine_table_32[32] = {
    512, 612, 707, 792, 866, 924, 966, 993,
    1004, 993, 966, 924, 866, 792, 707, 612,
    512, 412, 317, 232, 158, 100, 58, 31,
    20, 31, 58, 100, 158, 232, 317, 412
};

/**
 * @brief 生成连续正弦波输出（查表法）
 * @param htlc5615: TLC5615句柄指针
 * @param frequency_hz: 正弦波频率(Hz)
 * @retval TLC5615_StatusTypeDef: 操作状态
 */
TLC5615_StatusTypeDef TLC5615_GenerateContinuousSineWave(TLC5615_HandleTypeDef *htlc5615, float frequency_hz)
{
    uint8_t table_index;
    uint32_t period_us;
    uint32_t step_delay_us;

    if (htlc5615 == NULL || frequency_hz <= 0) {
        return TLC5615_ERROR;
    }

    // 计算正弦波周期(微秒)
    period_us = (uint32_t)(1000000.0f / frequency_hz);

    // 计算每个步进的延迟时间
    step_delay_us = period_us / 32;

    // 连续循环输出正弦波
        for (table_index = 0; table_index < 32; table_index++) {
            if (TLC5615_WriteValue(htlc5615, sine_table_32[table_index]) != TLC5615_OK) {
                return TLC5615_ERROR;
            }

            if (step_delay_us > 0) {
                if (step_delay_us >= 1000) {
                    HAL_Delay(step_delay_us / 1000);
                    TLC5615_Delay_us(step_delay_us % 1000);
                } else {
                    TLC5615_Delay_us(step_delay_us);
                }
            }
        }

    return TLC5615_OK;
}