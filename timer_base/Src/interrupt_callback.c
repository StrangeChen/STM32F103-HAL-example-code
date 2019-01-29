/*
 * CHEN QI
 * 2019/1/25
 * SHU-Strive
 *************************/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
#include "tim.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//注意是上升沿触发还是下降沿触发
	//以按键按下为1为例，及按下为上升沿，抬起为下降沿上升沿
	//这里选择上升沿中断
	if(GPIO_Pin == KEY2_Pin)
	{
		delay_ms(20); //消抖
		//若选择上升沿中断，这里则是 KEY == 1
		if(KEY2 == 1)
			LED_G = !LED_G;
		/*
		if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) == 0)
			HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);	
		*/
	}
}


Clock clock;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		printf("单片机运行时间为:  |%.2d:%.2d:%.2d| \r\n",clock.hour,clock.minute,clock.second);
		clock.second ++;
		if(clock.second == 60)
		{
			clock.second = 0;
			clock.minute ++;
		}
		if(clock.minute == 60)
		{
			clock.hour ++;
			clock.minute = 0;
		}
		
		LED_Off();
		switch(clock.second % 6)
		{
			case 0:
				LED_R = 0;
			break;
			case 2:
				LED_B = 0;
			break;
			case 4:
				LED_G = 0;
			break;
		}
		
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		//如果收到的是 ‘1’，led改变状态，并回复led状态
		if(rxBuf == '1')
		{
			LED_B = !LED_B;
			//中断函数中最好不要使用printf等串口发送操作，因为串口发送数据很耗时间
			//这里程序简单 无所谓
			if(LED_B == 0)	//低电平亮
				printf("灯亮了\r\n");
			else
				printf("灯灭了\r\n");

		}
		//否则将收到的数据传回
		else
			HAL_UART_Transmit(&huart1,&rxBuf,sizeof(rxBuf),100);
		
		HAL_UART_Receive_IT(&huart1,&rxBuf,sizeof(rxBuf));	//重新开启接收中断
	}
}

