#include "mbed.h"

AnalogOut ao(p18);

float t = 0.0f;

int main()
{
    for (t = 0.0f; t < 6.3f; t += 0.314f) {
        ao = (sin(t) + 1.0f)/ (2.0f) ;
    }
}