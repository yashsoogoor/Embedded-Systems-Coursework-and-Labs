#include "mbed.h"
PwmOut myled(LED1);
AnalogIn mypotentiometer(p20);
int main()
{
    while(1) {
        myled = mypotentiometer;
        wait(0.01);
    }
}