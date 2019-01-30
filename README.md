# STM32F103-HAL-example-code
stm32f103的HAL库例程  

### 软件版本
MDK: 5.26  
stm32cubemx: 4.27.0  
keil package: Keil.STM32F1 xx_DFP.2.1.0  
cube package: STM32Cube_FW_F1_V1.6.0
### 芯片&引脚定义 
stm32f103vet6 
|功能|引脚|
|---|---|
|led_green|PB0|
|led_blue|PB1|  
|led_red |PB5|  
|key_1|PA0| 
|key_2|PC13|  
### 文件说明
1. 基础代码均由cubemx生成
2. deley.c/delay.h 为延时函数实现，包括微秒级和毫秒级延时，弥补HAL_Delay()同过中断实现延时的缺陷
3. sys.h 文件中将常用数据类型简化，如`typedef uint8_t  u8;`，以及实现51类似的GPIO控制功能，eg：	`PAout(n),PAin(n) `
4. interrupt_callback.c为中断回调函数聚集地
### 例程说明
#### key_control_led
>按键控制led灯亮灭，按下按键改变led状态
#### key_control_led_by_interrupt
>通过EXIT中断方式，使用按键控制led亮灭，效果和上一程序相同
#### uart_receive_and_transmit
>|功能 |引脚 |
>|---|----|
>|RX|PA10|
>|TX|PA9|

>使用USART1，波特率9600，使用串口调试助手发送‘1’控制led翻转并回传告知灯亮/灯灭，发送其他字符单片机回传。
#### uart_receive_interrupt
> 通过串口接收中断实现上述操作，注意开启接收中断和中断回调函数的写法。
#### timer_base
> 定时器基础功能使用，使用TIM2，每一秒进一次中断，通过USART1打印出单片机运行时间，格式为：00:00:00，同时实现流水灯，红、蓝、绿三灯依次亮灭。注意定时器Prescaler和Counter Period参数配置。
#### timer_pwm
> 利用定时器输出PWM波，使用TIM3_CH3，映射至PB0，实现呼吸灯功能，及渐亮渐灭。注意注意定时器Prescaler和Counter Period参数配置；注意PWM Mode和CH Polarity配置。

