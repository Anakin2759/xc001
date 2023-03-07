#include<Arduino.h>
#include"tracing.h"
#include"mada.h"

void tracerReady()
{
    pinMode(39,INPUT);
    pinMode(36,INPUT);
    pinMode(35,INPUT);
    pinMode(34,INPUT);
}


void TSCANF()
{
    switch((digitalRead(34)<<2)|((digitalRead(35)||digitalRead(36))<<1)|digitalRead(39))
    {
        case 0b100:
            turnRight();
            break;
        case 0b001:
            turnLeft();
            break;
        case 0b111:
            stop();
        default :
        run();
    }
}
