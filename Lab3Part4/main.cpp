#include "mbed.h"
 
Ticker flipper1;
Ticker flipper2;
Ticker flipper3;
Ticker flipper4;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
 
void flip1() {
    led1 = !led1;
}
 
void flip2() {
    led2 = !led2;
}
 
void flip3() {
    led3 = !led3;
}
 
void flip4() {
    led4 = !led4;
}
 
int main() {
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    
    flipper1.attach(&flip1, 8.0); // the address of the function to be attached (flip1) and the interval (8 seconds)
    flipper2.attach(&flip2, 4.0); // the address of the function to be attached (flip2) and the interval (4 seconds)
    flipper3.attach(&flip3, 2.0); // the address of the function to be attached (flip3) and the interval (2 seconds)
    flipper4.attach(&flip4, 1.0); // the address of the function to be attached (flip4) and the interval (1 seconds)
}