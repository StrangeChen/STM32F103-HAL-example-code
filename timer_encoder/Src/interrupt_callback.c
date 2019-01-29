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


int speed;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		//每十毫秒都一次编码器数据，并将计数器清零，可当作轮子旋转速度
		speed = TIM3->CNT;
		TIM3->CNT = 0;	
		/*等价于
		*speed = __HAL_TIM_GET_COUNTER(&htim3);
		*__HAL_TIM_SET_COUNTER(&htim2, 0);
		************************************************/
		
		//这里为了展示 用了pritf，实际工程不要使用串口输出
		printf("%d \r\n",speed);
		
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

