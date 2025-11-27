//
// Created by 陈浩瑜 on 25-11-21.
//
#include "key.h"

#include <sys/lock.h>
uint8_t KEY_STATA0=0;

uint8_t key_scan(void) {
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_0;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_1;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_2;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_3;
        }
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_4;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_5;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_6;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_7;
        }
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_8;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_9;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_10;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_11;
        }
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_12;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_13;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_14;
        }
        else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==GPIO_PIN_RESET) {
            KEY_STATA0=1;
            return key_15;
        }
    KEY_STATA0=0;
    return 16;
}
// uint8_t key_scan(void) {
//     GPIO_InitTypeDef GPIO_InitStruct = {0};
//     GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
//     GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // 推挽输出模式
//     GPIO_InitStruct.Pull = GPIO_NOPULL;          // 无上下拉
//     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 低速
//     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//     GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
//     GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//     GPIO_InitStruct.Pull = GPIO_PULLUP;
//     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//     uint8_t deci=0;
//     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
//     if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET) {
//         deci|=0x01;
//     }
//     else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET) {
//         deci|=0x02;
//     }
//     else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==GPIO_PIN_RESET) {
//         deci|=0x04;
//     }
//     else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==GPIO_PIN_RESET) {
//         deci|=0x08;
//     }
//
//     GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
//     GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // 推挽输出模式
//     GPIO_InitStruct.Pull = GPIO_NOPULL;          // 无上下拉
//     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 低速
//     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//     GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
//     GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//     GPIO_InitStruct.Pull = GPIO_PULLUP;
//     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);
//     if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET) {
//         deci|=0x10;
//     }
//     else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET) {
//         deci|=0x20;
//     }
//     else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_RESET) {
//         deci|=0x40;
//     }
//     else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==GPIO_PIN_RESET) {
//         deci|=0x80;
//     }
//     switch(deci){
//         case 0x11:
//             KEY_STATA0=1;
//             return key_0;
//             break;
//         case 0x12:
//             KEY_STATA0=1;
//             return key_1;
//             break;
//         case 0x14:
//             KEY_STATA0=1;
//             return key_2;
//             break;
//         case 0x18:
//             KEY_STATA0=1;
//             return key_3;
//             break;
//         case 0x21:
//             KEY_STATA0=1;
//             return key_4;
//         case 0x22:
//             KEY_STATA0=1;
//             return key_5;
//             break;
//         case 0x24:
//             KEY_STATA0=1;
//             return key_6;
//             break;
//         case 0x28:
//             KEY_STATA0=1;
//             return key_7;
//             break;
//         case 0x41:
//             KEY_STATA0=1;
//             return key_8;
//             break;
//         case 0x42:
//             KEY_STATA0=1;
//             return key_9;
//             break;
//         case 0x44:
//             KEY_STATA0=1;
//             return key_10;
//             break;
//         case 0x48:
//             KEY_STATA0=1;
//             return key_11;
//             break;
//         case 0x81:
//             KEY_STATA0=1;
//             return key_12;
//             break;
//         case 0x82:
//             KEY_STATA0=1;
//             return key_13;
//             break;
//         case 0x84:
//             KEY_STATA0=1;
//             return key_14;
//             break;
//         case 0x88:
//             KEY_STATA0=1;
//             return key_15;
//             break;
//         default:
//             KEY_STATA0=0;
//             return 16;
//             break;
//     }
// }
//按键获取函数，按下按键30ms的按键抖动，
//2s内松开视为有效单击，0.5s后无按键按下，结算总共按下几次有效单击，
//单击返回1，双击返回2，三击返回3，长击返回10；
//用不到三击以上的按键，而且十击与长按都返回10，之后可能会出巨大的事故问题
uint8_t Keyval_Scan(void)
{
    static uint16_t key_state, key_time, key_cnt;
    uint8_t key_return = 0;

    switch(key_state) {
        case 0://按键状态0:判断有无按键按下
            if(KEY_STATA0) {
                key_time = 0;//按键按下时,按键计时器清0
                key_state = 1;//按键状态置1
            }
            break;
        case 1://按键状态1:按键消抖
            if(KEY_STATA0) {
                HAL_Delay(0);
                if(key_time++ >= 30)
                    key_state = 2;//当按键按下超过30ms时,进入按键单击状态
            }
            else key_state = 0;//松开按键,视为误触
            break;
        case 2://按键状态2:单击或长击
            if(!KEY_STATA0) {
                key_time = 0;
                key_cnt++;//按键计数器自增
                key_state = 3;//此时按键松开,表示已经单击,进入下个状态
            }
            else {
                HAL_Delay(0);
                if(key_time++ >= 2000) {
                    key_cnt = 0;
                    key_return = 10;
                    key_state = 4;
                }
            }
            break;
        case 3://按键状态3:按键多击
            if(!KEY_STATA0) {
                HAL_Delay(0);
                if(key_time++ >= 500) {//松开按键0.5s无按键按下,返回按键计数器
                    key_return = key_cnt;
                    key_cnt = 0;
                    key_state = 0;
                }
            }
            else {
                key_state = 0;
            }
            break;
        case 4://按键状态4:等待长按按键释放
            if(!KEY_STATA0) key_state = 0;
            break;
    }

    return key_return;
}
