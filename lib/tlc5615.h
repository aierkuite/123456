//
// Created by 陈浩瑜 on 25-11-19.
//

#ifndef TLC5615_H
#define TLC5615_H
// TLC5615引脚定义 - 根据实际连接修改
#define TLC5615_CS_PIN     GPIO_PIN_4
#define TLC5615_CS_PORT    GPIOA
#define TLC5615_SCLK_PIN   GPIO_PIN_5
#define TLC5615_SCLK_PORT  GPIOA
#define TLC5615_DIN_PIN    GPIO_PIN_7
#define TLC5615_DIN_PORT   GPIOA
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>


// 错误代码定义
typedef enum {
    TLC5615_OK      = 0x00,
    TLC5615_ERROR   = 0x01,
    TLC5615_TIMEOUT = 0x02
} TLC5615_StatusTypeDef;

// TLC5615配置结构体
typedef struct {
    GPIO_TypeDef* cs_port;
    uint16_t cs_pin;
    GPIO_TypeDef* sclk_port;
    uint16_t sclk_pin;
    GPIO_TypeDef* din_port;
    uint16_t din_pin;
    float ref_voltage;
    uint32_t timeout;
} TLC5615_HandleTypeDef;

// 函数声明
TLC5615_StatusTypeDef TLC5615_Init(TLC5615_HandleTypeDef* htlc5615);
TLC5615_StatusTypeDef TLC5615_WriteValue(TLC5615_HandleTypeDef* htlc5615, uint16_t value);
TLC5615_StatusTypeDef TLC5615_WriteVoltage(TLC5615_HandleTypeDef* htlc5615, float voltage);
TLC5615_StatusTypeDef TLC5615_SetReferenceVoltage(TLC5615_HandleTypeDef* htlc5615, float ref_voltage);
float TLC5615_GetOutputVoltage(TLC5615_HandleTypeDef* htlc5615, uint16_t digital_value);
TLC5615_StatusTypeDef TLC5615_PowerDown(TLC5615_HandleTypeDef* htlc5615);
TLC5615_StatusTypeDef TLC5615_WakeUp(TLC5615_HandleTypeDef* htlc5615);
TLC5615_StatusTypeDef TLC5615_DaisyChainWrite(TLC5615_HandleTypeDef* htlc5615, uint16_t* values, uint8_t device_count);
TLC5615_StatusTypeDef TLC5615_DeInit(TLC5615_HandleTypeDef* htlc5615);
void TLC5615_OutSignal(TLC5615_HandleTypeDef *htlc5615, uint16_t *value_table,uint8_t beishu);
// 高级功能
typedef struct {
    uint16_t min_value;
    uint16_t max_value;
    uint16_t step;
    uint32_t delay_ms;
} TLC5615_WaveformConfigTypeDef;

TLC5615_StatusTypeDef TLC5615_GenerateWaveform(TLC5615_HandleTypeDef* htlc5615, TLC5615_WaveformConfigTypeDef* config);
const uint16_t sine_table[90];
const uint16_t triangle_table[90];
const uint16_t square_table[90];
#endif //TLC5615_H
