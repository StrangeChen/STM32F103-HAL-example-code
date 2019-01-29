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


int speed;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		//ÿʮ���붼һ�α��������ݣ��������������㣬�ɵ���������ת�ٶ�
		speed = TIM3->CNT;
		TIM3->CNT = 0;	
		/*�ȼ���
		*speed = __HAL_TIM_GET_COUNTER(&htim3);
		*__HAL_TIM_SET_COUNTER(&htim2, 0);
		************************************************/
		
		//����Ϊ��չʾ ����pritf��ʵ�ʹ��̲�Ҫʹ�ô������
		printf("%d \r\n",speed);
		
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

