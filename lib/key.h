//
// Created by 陈浩瑜 on 25-11-21.
//

#ifndef KEY_H
#define KEY_H
#include <stdint.h>
#include "main.h"

typedef enum {
    key_0 = 0,
    key_1 = 1,
    key_2 = 2,
    key_3 = 3,
    key_4 = 4,
    key_5 = 5,
    key_6 = 6,
    key_7 = 7,
    key_8 = 8,
    key_9 = 9,
    key_10 = 10,
    key_11 = 11,
    key_12 = 12,
    key_13 = 13,
    key_14 = 14,
    key_15 = 15
}key_type;
uint8_t key_scan(void);
uint8_t Keyval_Scan(void);

#endif //KEY_H
