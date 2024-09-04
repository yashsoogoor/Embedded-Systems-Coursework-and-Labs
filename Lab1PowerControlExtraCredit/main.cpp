#include "mbed.h"
#include "PowerControl/PowerControl.h"
#include "PowerControl/EthernetPowerControl.h"


//Without Power Control ------------------------------------------
DigitalIn enable(p8);
DigitalOut led(p21);
 
int main() {
    //enable.mode(PullUp);
    while(1) {
        if (!enable) led = 1;
        else led = 0;
       
        
       
        wait(0.25);
    }
}
// End Without Power Control ------------------------------------


/*
//With Power Control --------------------------------------------

// Need PowerControl *.h files from this URL
// http://mbed.org/users/no2chem/notebook/mbed-power-controlconsumption/

// Function to power down magic USB interface chip with new firmware
#define USR_POWERDOWN    (0x104)
int semihost_powerdown() {
    uint32_t arg;
    return __semihost(USR_POWERDOWN, &arg);
}

DigitalIn enable(p8);
DigitalOut led(p21);

Ticker blinker;
int count=1;

void blink() {
    //enable.mode(PullUp);
    while(1) {
        if (!enable) led = 1;
        else led = 0;
       
        
       
        wait(0.25);
    }
}

int main() {
    int result;
// Normal mbed power level for this setup is around 690mW
// assuming 5V used on Vin pin
// If you don't need networking...
// Power down Ethernet interface - saves around 175mW
// Also need to unplug network cable - just a cable sucks power
    PHY_PowerDown();

// If you don't need the PC host USB interface....
// Power down magic USB interface chip - saves around 150mW
// Needs new firmware (URL below) and USB cable not connected
// http://mbed.org/users/simon/notebook/interface-powerdown/
// Supply power to mbed using Vin pin
    result = semihost_powerdown();
// Power consumption is now around half

// Turn off clock enables on unused I/O Peripherals (UARTs, Timers, PWM, SPI, CAN, I2C, A/D...)
// To save just a tiny bit more power - most are already off by default in this short code example
// See PowerControl.h for I/O device bit assignments
// Don't turn off GPIO - it is needed to blink the LEDs
    Peripheral_PowerDown(0xFFFF7FFF);

// use Ticker interrupt and Sleep instead of a wait for time delay - saves up to 70mW
// Sleep halts and waits for an interrupt instead of executing instructions
// power is saved by not constantly fetching and decoding instructions
// Exact power level reduction depends on the amount of time spent in Sleep mode
    blinker.attach(&blink, 0.0625);
    while (1) {
        Sleep();
    }
}

// End With Power Control -----------------------------------------------
*/
