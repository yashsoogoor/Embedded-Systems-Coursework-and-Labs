// Sweep the motor speed from full-speed reverse (-1.0) to full speed forwards (1.0)

#include "mbed.h"
#include "Motor.h"

Motor m(p23, p6, p5); // pwm, fwd, rev
AnalogIn myPot(p15);
DigitalOut STBY(p21);

int main()
{
    while (1) {
        STBY = 1;
        m.speed(2*myPot-1);
        //m.speed(.5);
    }
}


