#include <Arduino.h>
#include <telecontrol.h>
#include <mada.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

IRrecv IRC1(33);
decode_results results;//设置解码类型
void IRstart()
{
    
    Serial.begin(9600);//串口波特率
    IRC1.enableIRIn();//启动
    delay(50);
}
void IRread()
{
    while(1)
    {
        if(IRC1.decode(&results))
        {
            serialPrintUint64(results.value,HEX);
            Serial.println(" ");
            if(results.value==0x979AE9E7)
            {
                madaReady();
                run();
            }
            IRC1.resume();
        }
       
    }
}