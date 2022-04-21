#include "mbed.h"
#include "PinDetect.h"
//#include "USBMouse.h"

Serial pc(USBTX,USBRX);
DigitalOut led1(LED1); 
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
DigitalIn pbjl(p5);
DigitalIn pbjr(p6);
DigitalIn pb1(p7);
DigitalIn pb2(p8);
DigitalIn pb3(p9);
DigitalIn pb4(p10);  
AnalogIn AnalogXl(p15);
AnalogIn AnalogYl(p16);
AnalogIn AnalogXr(p17);
AnalogIn AnalogYr(p18); 


int main(void)
{   
    pbjl.mode(PullUp);
    pbjr.mode(PullUp);
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);
    while (1)
    {
       // pc.printf("%f",AnalogXl.read());
//        pc.printf("%f",AnalogYl.read());
//        pc.printf("%f",AnalogXr.read());
//        pc.printf("%f",AnalogYr.read());
        
        led1 = pb1;
        led2 = pb2;
        led3 = pb3; 
        led4 = pb4; 
        
        if (!pbjl)
        {
            pc.printf("Joystick 1");
        }
        if (!pbjr)
        {
            pc.printf("Joystick 2");
        }
    }
 }
