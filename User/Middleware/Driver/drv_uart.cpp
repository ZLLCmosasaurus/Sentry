/**
 * @file drv_uart.cpp
 * @author lez by yssickjgd
 * @brief UART通信初始化与配置流程
 * @version 0.1
 * @date 2024-07-1 0.1 24赛季定稿
 *
 * @copyright ZLLC 2024
 * 
 */

/* Includes ------------------------------------------------------------------*/

#include "drv_uart.h"
#include "string.h"
/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

Struct_UART_Manage_Object UART1_Manage_Object = {0};
Struct_UART_Manage_Object UART2_Manage_Object = {0};
Struct_UART_Manage_Object UART3_Manage_Object = {0};
Struct_UART_Manage_Object UART4_Manage_Object = {0};
Struct_UART_Manage_Object UART5_Manage_Object = {0};
Struct_UART_Manage_Object UART6_Manage_Object = {0};
Struct_UART_Manage_Object UART7_Manage_Object = {0};
Struct_UART_Manage_Object UART10_Manage_Object = {0};

/* Private function declarations ---------------------------------------------*/

/* function prototypes -------------------------------------------------------*/

/**
 * @brief 初始化UART
 *
 * @param huart UART编号
 * @param Callback_Function 处理回调函数
 */
void UART_Init(UART_HandleTypeDef *huart, UART_Call_Back Callback_Function, uint16_t Rx_Buffer_Length)
{
    if (huart->Instance == USART1)
    {
        UART1_Manage_Object.UART_Handler = huart;
        UART1_Manage_Object.Callback_Function = Callback_Function;
        UART1_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART1_Manage_Object.Rx_Buffer, UART1_Manage_Object.Rx_Buffer_Length);
			//__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);  //暂时注释
    }
    else if (huart->Instance == UART5)
    {
        UART5_Manage_Object.UART_Handler = huart;
        UART5_Manage_Object.Callback_Function = Callback_Function;
        UART5_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART5_Manage_Object.Rx_Buffer, UART5_Manage_Object.Rx_Buffer_Length);
			__HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_HT);
    }
    else if (huart->Instance == UART7)
    {
        UART7_Manage_Object.UART_Handler = huart;
        UART7_Manage_Object.Callback_Function = Callback_Function;
        UART7_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART7_Manage_Object.Rx_Buffer, UART7_Manage_Object.Rx_Buffer_Length);
				//__HAL_DMA_DISABLE_IT(&hdma_usart7_rx, DMA_IT_HT);
    }
    else if (huart->Instance == USART10)
    {
        UART10_Manage_Object.UART_Handler = huart;
        UART10_Manage_Object.Callback_Function = Callback_Function;
        UART10_Manage_Object.Rx_Buffer_Length = Rx_Buffer_Length;
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART10_Manage_Object.Rx_Buffer, UART10_Manage_Object.Rx_Buffer_Length);
				//__HAL_DMA_DISABLE_IT(&hdma_usart10_rx, DMA_IT_HT);
    }
}

/**
 * @brief 发送数据帧
 *
 * @param huart UART编号
 * @param Data 被发送的数据指针
 * @param Length 长度
 * @return uint8_t 执行状态
 */
uint8_t UART_Send_Data(UART_HandleTypeDef *huart, uint8_t *Data, uint16_t Length)
{
    return (HAL_UART_Transmit_DMA(huart, Data, Length));
}

/**
 * @brief UART的TIM定时器中断发送回调函数
 *
 */
void TIM_UART_PeriodElapsedCallback()
{
    // UART1超电通讯
    UART_Send_Data(&huart1, UART1_Manage_Object.Tx_Buffer, 10);
}

/**
 * @brief HAL库UART接收DMA空闲中断
 *
 * @param huart UART编号
 * @param Size 长度
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{    
    //停止DMA接收 保护处理过程
//    HAL_UART_DMAStop(huart);
    //选择回调函数
    if (huart->Instance == USART1)
    {
        UART1_Manage_Object.Rx_Length = Size;
        UART1_Manage_Object.Callback_Function(UART1_Manage_Object.Rx_Buffer, Size);
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART1_Manage_Object.Rx_Buffer, UART1_Manage_Object.Rx_Buffer_Length);
				//__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
    }
    else if (huart->Instance == UART5)
    {
        UART5_Manage_Object.Rx_Length = Size;
        UART5_Manage_Object.Callback_Function(UART5_Manage_Object.Rx_Buffer, Size);
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART5_Manage_Object.Rx_Buffer, UART5_Manage_Object.Rx_Buffer_Length);
				__HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_HT);
    }
    else if (huart->Instance == UART7)
    {
        UART7_Manage_Object.Rx_Length = Size;
        UART7_Manage_Object.Callback_Function(UART7_Manage_Object.Rx_Buffer, Size);
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART7_Manage_Object.Rx_Buffer, UART7_Manage_Object.Rx_Buffer_Length);
				//__HAL_DMA_DISABLE_IT(&hdma_usart6_rx, DMA_IT_HT);
    }
    else if (huart->Instance == USART10)
    {
        UART10_Manage_Object.Rx_Length = Size;
        UART10_Manage_Object.Callback_Function(UART10_Manage_Object.Rx_Buffer, Size);
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART10_Manage_Object.Rx_Buffer, UART10_Manage_Object.Rx_Buffer_Length);
				//__HAL_DMA_DISABLE_IT(&hdma_usart6_rx, DMA_IT_HT);
    }    
}
//void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
//{
//	if (huart->Instance == USART3)
//    {
//        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART3_Manage_Object.Rx_Buffer, UART3_Manage_Object.Rx_Buffer_Length);
//				__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);	
//		}
//}
/************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/
