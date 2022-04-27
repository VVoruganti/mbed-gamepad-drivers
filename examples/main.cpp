#include "mbed.h"
#include "USBMouse.h"
#include "USBGamepad.h"
//#include "PinDetect.h"

// USBGamepad gamepad;
USBMouse mouse;


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
 
AnalogIn AnalogYr(p18); 
AnalogIn AnalogXr(p19);

uint8_t button;

int main(void)
{   
    pc.printf("Welcome\r\n");
    
    pbjl.mode(PullUp);
    pbjr.mode(PullUp);
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);
    
    led1 = 1;
    
    while (1)
    {
        button = 0;
        
        //pc.printf("| X1 %f |",AnalogXl.read());
//        pc.printf("| Y1 %f |",AnalogYl.read());
//        pc.printf("| X2 %f |",AnalogXr.read());
//        pc.printf("| Y2 %f |\r\n",AnalogYr.read());    
        
        if (!pb1) {
            button = button ^ 0x01;
        }
        if (!pb2) {
            button = button ^ 0x02;
        }
        if (!pb3) {
            button = button ^ 0x03;
        }
        if (!pb4) {
            button = button ^ 0x04;
        }
        if (!pbjl) {
            button = button ^ 0x05;
        }
        if (!pbjr) {
            button = button ^ 0x06;
        }
        
        // led1 = !pb1 || !pbjl;
        // led2 = !pb2;
        // led3 = !pb3; 
        // led4 = !pb4 || !pbjr; 
        
        int8_t x = (AnalogXl.read() * 254 - 127);
        int8_t y = (AnalogYl.read() * 254 - 127);
        int8_t z = (AnalogXr.read() * 254 - 127);
        int8_t xr = (AnalogYr.read() * 254 - 127);
        
        mouse.update(x, y, pb1, 0);
        
        // gamepad.update(x, y, button, z, xr);    
        wait(0.001);    

    }
 }
