/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tlc5615.h"
#include "key.h"
#include "oled.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void Menu_Interface(void);
void Function_Interface1(void);
void Function_Interface2(void);
void Function_Interface3(void);
void Function_Interface4(void);
void Function_Interface5(void);
void Function_Interface6(void);

uint8_t taskIndex = 0;	//任务调度序号

typedef struct
{
  uint8_t CurrentNum;	//当前索引序号:页码
  uint8_t Enter;		//确认键
  uint8_t Next;		//下一个
  uint8_t Return;		//返回键
  void (*Current_Operation)(void);//当前操作(函数指针)
}Menu_table_t;

Menu_table_t taskTable[] =
{
  //菜单界面函数 -- 一级界面
  {0, 1, 0, 0, Menu_Interface},
  //功能界面函数 -- 二级界面
  {1, 4, 2, 0, Function_Interface1},
  {2, 5, 1, 0, Function_Interface2},
  {3, 6, 1, 0, Function_Interface3},
//功能设置界面函数 -- 三级界面
{4, 4, 4, 1, Function_Interface4},
{5, 5, 5, 2, Function_Interface5},
{6, 6, 6, 3, Function_Interface6},

};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void Menu_Interface(void)
{
  static uint8_t i=0;
  OLED_NewFrame();
  OLED_DrawCircle(64,32,i,OLED_COLOR_NORMAL);
  OLED_DrawCircle(64,32,2*i,OLED_COLOR_NORMAL);
  OLED_DrawCircle(64,32,3*i,OLED_COLOR_NORMAL);
  OLED_PrintString(27, 20, "信号发生器", &font16x16, OLED_COLOR_NORMAL);
  OLED_ShowFrame();
  i++;
  if (i==64) {
    i=0;
  }
}
void Function_Interface1(void)
{
  OLED_NewFrame();
  OLED_PrintString(0, 0, ">>正弦波", &font16x16, OLED_COLOR_NORMAL);
  OLED_PrintString(0, 20, "方波", &font16x16, OLED_COLOR_NORMAL);
  OLED_PrintString(0, 40, "三角波", &font16x16, OLED_COLOR_NORMAL);
  OLED_ShowFrame();
}
void Function_Interface2(void)
{
  OLED_NewFrame();
  OLED_PrintString(0, 0, "正弦波", &font16x16, OLED_COLOR_NORMAL);
  OLED_PrintString(0, 20, ">>方波", &font16x16, OLED_COLOR_NORMAL);
  OLED_PrintString(0, 40, "三角波", &font16x16, OLED_COLOR_NORMAL);
  OLED_ShowFrame();
}
void Function_Interface3(void)
{
  OLED_NewFrame();
  OLED_PrintString(0, 0, "正弦波", &font16x16, OLED_COLOR_NORMAL);
  OLED_PrintString(0, 20, "方波", &font16x16, OLED_COLOR_NORMAL);
  OLED_PrintString(0, 40, ">>三角波", &font16x16, OLED_COLOR_NORMAL);
  OLED_ShowFrame();
}
void Function_Interface4(void)
{
  OLED_NewFrame();
  OLED_PrintString(0, 0, "111", &font16x16, OLED_COLOR_NORMAL);
  OLED_ShowFrame();
}
void Function_Interface5(void)
{
  OLED_NewFrame();
  OLED_PrintString(0, 0, "222", &font16x16, OLED_COLOR_NORMAL);
  OLED_ShowFrame();
}
void Function_Interface6(void)
{
  OLED_NewFrame();
  OLED_PrintString(0, 0, "333", &font16x16, OLED_COLOR_NORMAL);
  OLED_ShowFrame();
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(20);
  OLED_Init();
  TLC5615_HandleTypeDef htlc5615;
  uint8_t cnt=0;
  // 初始化TLC5615
  htlc5615.cs_port = GPIOA;
  htlc5615.cs_pin = GPIO_PIN_4;
  htlc5615.sclk_port = GPIOA;
  htlc5615.sclk_pin = GPIO_PIN_5;
  htlc5615.din_port = GPIOA;
  htlc5615.din_pin = GPIO_PIN_7;
  htlc5615.ref_voltage = 3.3f;  // 参考电压设置为3.3V
  htlc5615.timeout = 100;

  TLC5615_Init(&htlc5615);
  uint8_t last_key;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    uint8_t keyty=key_scan();
    if (keyty!=16) {
      last_key=keyty;
    }
    uint8_t val=Keyval_Scan();
    if (val!=0) {
      switch (last_key) {
        case key_0:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_0\r\n", sizeof("key_0\r\n"), 100);
        case key_1:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_1\r\n", sizeof("key_1\r\n"), 100);
          break;
        case key_2:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_2\r\n", sizeof("key_2\r\n"), 100);
          break;
        case key_3:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_3\r\n", sizeof("key_3\r\n"), 100);
          break;
        case key_4:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_4\r\n", sizeof("key_4\r\n"), 100);
          taskIndex = taskTable[taskIndex].Enter;//双击表示确认键
          break;
        case key_5:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_5\r\n", sizeof("key_5\r\n"), 100);
          taskIndex = taskTable[taskIndex].Return;//长击表示返回键
          break;
        case key_6:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_6\r\n", sizeof("key_6\r\n"), 100);
          taskIndex = taskTable[taskIndex].Next;//单击表示下一位键
          break;
        case key_7:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_7\r\n", sizeof("key_7\r\n"), 100);
          break;
        case key_8:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_8\r\n", sizeof("key_8\r\n"), 100);
          break;
        case key_9:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_9\r\n", sizeof("key_9\r\n"), 100);
          break;
        case key_10:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_10\r\n", sizeof("key_10\r\n"), 100);
          break;
        case key_11:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_11\r\n", sizeof("key_11\r\n"), 100);
          break;
        case key_12:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_12\r\n", sizeof("key_12\r\n"), 100);
          break;
        case key_13:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_13\r\n", sizeof("key_13\r\n"), 100);
          break;
        case key_14:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_14\r\n", sizeof("key_14\r\n"), 100);
          break;
        case key_15:
          HAL_UART_Transmit(&huart1, (uint8_t*)"key_15\r\n", sizeof("key_15\r\n"), 100);
          break;
        default:
          break;
      }
    }
    if(cnt++ >= 200) {
      cnt = 0;
      taskTable[taskIndex].Current_Operation();//执行函数
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
