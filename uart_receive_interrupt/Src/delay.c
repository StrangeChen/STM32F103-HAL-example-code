#include "delay.h"

//延时nus
//nus为要延时的us数.	
//nus:最大值即2^32/(SystemCoreClock/1000000)
void delay_us(uint32_t nus)
{		
	uint32_t ticks,t_start,t_now,tcnt = 0;	    	 
	uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
	ticks = nus*(SystemCoreClock/1000000); 		//需要的节拍数 ,注意一定要加上括号
	t_start=SysTick->VAL;        				//刚进入时的计数器值
	while(1)
	{
		t_now=SysTick->VAL;	
		if(t_now!=t_start)
		{	    
			if(t_now<t_start)
				tcnt += t_start - t_now;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else 
				tcnt += reload - t_now + t_start;	    
			t_start = t_now;	
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	}
}


//延时nms
//nms:要延时的ms数
void delay_ms(uint32_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}

































