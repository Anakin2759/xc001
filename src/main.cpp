#include <Arduino.h>
#include <music.h>
#include<mada.h>
#include<tracing.h>
#include<freertos/freeRTOS.h>
#include<freertos/task.h>
#include<telecontrol.h>
#include<WIFIcontrol.h>
#include<main.h>

#define TASK_STACK_SIZE 5000
QueueHandle_t queue;
// 定义任务句柄
TaskHandle_t Task1Handle = nullptr;
TaskHandle_t Task2Handle = nullptr;
TaskHandle_t Task3Handle = nullptr;
TaskHandle_t Task4Handle = nullptr;

void Tracer(void *pvParameters)
{
  while(1)
  {
    TSCANF();
  }
}

// 任务1函数
void mada_diver(void *pvParameters) {

  while(1)
  {
    uint32_t data;  
    xQueueReceive(queue, &data, 1000);
    switch(data)
    {
      case 0:
        run();
        break;
      case 1:
        back();
        break;
      case 2:
      case 3:
      case 4:
      stop();
        break;
      case 5:
        xTaskCreate(Tracer, "Tracer", TASK_STACK_SIZE, NULL, 1,&Task4Handle );

      case 6:
        vTaskDelete(Task4Handle);
        stop();
      default:
      ;
    }
  }
  

}

// 任务2函数
void wifi_ctr(void *pvParameters) {
  wifiReady();
  wifirun();// 延时 2000 毫秒
  vTaskDelete(NULL);
}



void musicPlay(void *pvParameters)
{
  music();
}

void setup() {
  madaReady();
  Serial.begin(9600);
  queue = xQueueCreate(5, sizeof(uint32_t));
  uint32_t data = 12345;
  if (xQueueSend(queue, &data, 1000) != pdPASS) {Serial.printf("发送失败");}

  // 创建任务
  xTaskCreate(mada_diver, "madadiver", TASK_STACK_SIZE, NULL,1, &Task1Handle);
  xTaskCreate(wifi_ctr, "wifictr", TASK_STACK_SIZE, NULL, 1, &Task2Handle);
  xTaskCreate(musicPlay, "musicPlay", TASK_STACK_SIZE, NULL, 1, &Task3Handle);
  
}

void loop() {
}