
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "can.h"
#include "FreeRTOS.h"
#include "task.h"
#include "SEGGER_SYSVIEW.h"

#define START_TASK_PRIO        1                    
#define START_STK_SIZE         128                  
TaskHandle_t StartTask_Handler;            
void start_task(void *pvParameters);
 
#define LED1_TASK_PRIO        3                    
#define LED1_STK_SIZE         50                  
TaskHandle_t LED1Task_Handler;            
void led1_task(void *pvParameters);    
 
#define LED2_TASK_PRIO        3                    
#define LED2_STK_SIZE         50                  
TaskHandle_t LED2Task_Handler;            
void led2_task(void *pvParameters);   

#define CAN_TASK_PRIO        2                    
#define CAN_STK_SIZE         250                  
TaskHandle_t CanTask_Handler;            
void can_task(void *pvParameters);   

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();
    // LED1
    xTaskCreate((TaskFunction_t )led1_task,         
                (const char*    )"led1_task",       
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,                
                (UBaseType_t    )LED1_TASK_PRIO,    
                (TaskHandle_t*  )&LED1Task_Handler);   
    // LED2 
    xTaskCreate((TaskFunction_t )led2_task,     
                (const char*    )"led2_task",   
                (uint16_t       )LED2_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED2_TASK_PRIO,
                (TaskHandle_t*  )&LED2Task_Handler);

    // CAN 
    xTaskCreate((TaskFunction_t )can_task,     
                (const char*    )"can_task",   
                (uint16_t       )CAN_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )CAN_TASK_PRIO,
                (TaskHandle_t*  )&CanTask_Handler);  
								
    vTaskDelete(StartTask_Handler); 
    taskEXIT_CRITICAL();            
}

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	USART1_Init(9600);
	KEY_Init();

  xTaskCreate((TaskFunction_t )start_task,            
              (const char*    )"start_task",          
              (uint16_t       )START_STK_SIZE,        
              (void*          )NULL,                  
              (UBaseType_t    )START_TASK_PRIO,       
              (TaskHandle_t*  )&StartTask_Handler);   

	// For systemView
	SEGGER_SYSVIEW_Conf();
  vTaskStartScheduler();   
}



 
void led1_task(void *pvParameters)
{
    while(1)
    {
			led1=~led1;
			printf("\n Task1 Running\n");
			vTaskDelay(500);
    }
}   
 
void led2_task(void *pvParameters)
{
    while(1)
    {
			led2=~led2;
			printf("\n Task2 Running\n");
			vTaskDelay(1000);
    }
}

void can_task(void *pvParameters)
{
	u8 i=0,j=0;
	u8 key;
	u8 mode=0;
	u8 res;
	u8 tbuf[8],char_buf[8];
	u8 rbuf[8];
	
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//500Kbps波特率
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY_UP)  //模式切换
		{
			mode=!mode;
			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,mode);
			if(mode==0)
			{
				printf("Normal Mode\r\n");
			}
			else
			{
				printf("LoopBack Mode\r\n");
			}
	
		}
		if(key==KEY_DOWN)  //发送数据
		{
			for(j=0;j<8;j++)
			{
				tbuf[j]=j;
				char_buf[j]=tbuf[j]+0x30;
			}
			res=CAN_Send_Msg(tbuf,8);
			if(res)
			{
				printf("Send Failed!\r\n");
			}
			else
			{
				printf("发送数据：%s\r\n",char_buf);
			}
			
		}
		res=CAN_Receive_Msg(rbuf);
		if(res)
		{
			for(j=0;j<res;j++)
			{
				char_buf[j]=rbuf[j]+0x30;
			}
			printf("接收数据：%s\r\n",char_buf);
		}
		
		i++;
		if(i%20==0)
		{
			led3=!led3;
		}
		printf("\n CAN Task Running \n");
		vTaskDelay(200);
	}
}
