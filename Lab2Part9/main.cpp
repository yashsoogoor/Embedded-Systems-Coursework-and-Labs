// Hello World to sweep a servo through its full range

#include "mbed.h"
#include "Servo.h"

Servo myservo(p21);

int main()
{
    while (1) {
        for(float p=0; p<1.0; p += 0.1) {
            myservo = p;
            wait(0.2);
        }
        for(float p=1.0; p>0; p -= 0.1) {
            myservo = p;
            wait(0.2);
        }
    }
}
