#include "mbed.h"

extern "C" int my_asm(int value);

DigitalOut led(p21);
DigitalIn pb(p8);

int main()
{
    while(1) {
        my_asm(!pb);
    }
}