#include "mbed.h"

PwmOut mymot(p21);

int main()
{
    while (1) {
        for (float i = 0.0; i < 1.0; i += 0.02) {
            mymot = i;
            wait(0.05);
        }
        for (float i = 1.0; i > 0.0; i -= 0.02) {
            mymot = i;
            wait(0.05);
        }
    }
}
