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
	//ע���������ش��������½��ش���
	//�԰�������Ϊ1Ϊ����������Ϊ�����أ�̧��Ϊ�½���������
	//����ѡ���������ж�
	if(GPIO_Pin == KEY2_Pin)
	{
		delay_ms(20); //����
		//��ѡ���������жϣ��������� KEY == 1
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
		printf("��Ƭ������ʱ��Ϊ:  |%.2d:%.2d:%.2d| \r\n",clock.hour,clock.minute,clock.second);
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
		//����յ����� ��1����led�ı�״̬�����ظ�led״̬
		if(rxBuf == '1')
		{
			LED_B = !LED_B;
			//�жϺ�������ò�Ҫʹ��printf�ȴ��ڷ��Ͳ�������Ϊ���ڷ������ݺܺ�ʱ��
			//�������� ����ν
			if(LED_B == 0)	//�͵�ƽ��
				printf("������\r\n");
			else
				printf("������\r\n");

		}
		//�����յ������ݴ���
		else
			HAL_UART_Transmit(&huart1,&rxBuf,sizeof(rxBuf),100);
		
		HAL_UART_Receive_IT(&huart1,&rxBuf,sizeof(rxBuf));	//���¿��������ж�
	}
}

