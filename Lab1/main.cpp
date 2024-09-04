#include "mbed.h"
#include "PinDetect.h"


//Part 1 -------------------------------------------------
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
// End Part 1 ------------------------------------------


/*
// Part 2 -----------------------------------------------

// must import Cookbook PinDetct library into project
// URL: http://mbed.org/users/AjK/libraries/PinDetect/lkyxpw

PwmOut myled(LED1);
PwmOut monitor(p26);

PinDetect pb1(p8);
PinDetect pb2(p16);

// SPST Pushbutton debounced count demo using interrupts and callback
// no external PullUp resistor needed
// Pushbutton from P8 to GND.
// Second Pushbutton from P7 to GND.
// A pb hit generates an interrupt and activates the callback function
// after the switch is debounced

// Global pwm variable
float volatile pwm=1.0f;

// Callback routine is interrupt activated by a debounced pb1 hit
void pb1_hit_callback (void)
{
    pwm -= 0.1f;
    if (pwm < 0.0f) {
        pwm = 0.0f;
    }
}

// Callback routine is interrupt activated by a debounced pb2 hit
void pb2_hit_callback (void)
{
    pwm += 0.1f;
    if (pwm > 1.0f) {
        pwm = 1.0f;
    }
}

int main()
{

    // Use internal pullups for pushbutton
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    // Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    // Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();

    while (1) {
        myled = pwm;
        monitor = pwm;
    }

}

//End Part 2 ------------------------------------------
*/

/*
//Part 3

//Class to control an RGB LED using three PWM pins
class RGBLed
{
public:
    RGBLed(PinName redpin, PinName greenpin, PinName bluepin);
    void write(float red,float green, float blue);
private:
    PwmOut _redpin;
    PwmOut _greenpin;
    PwmOut _bluepin;
};

RGBLed::RGBLed (PinName redpin, PinName greenpin, PinName bluepin)
    : _redpin(redpin), _greenpin(greenpin), _bluepin(bluepin)
{
    //50Hz PWM clock default a bit too low, go to 2000Hz (less flicker)
    _redpin.period(0.0005);
}

void RGBLed::write(float red,float green, float blue)
{
    _redpin = red;
    _greenpin = green;
    _bluepin = blue;
}

//Setup RGB led using PWM pins and class
RGBLed myRGBled(p21,p22,p23); //RGB PWM pins

DigitalIn r(p24);
DigitalIn g(p25);
DigitalIn b(p26);

PinDetect pb1(p8);
PinDetect pb2(p16);

// Global pwm variable
float volatile pwm=1.0f;

// Callback routine is interrupt activated by a debounced pb1 hit
void pb1_hit_callback (void)
{
    pwm -= 0.1f;
    if (pwm < 0.0f) {
        pwm = 0.0f;
    }
}

// Callback routine is interrupt activated by a debounced pb2 hit
void pb2_hit_callback (void)
{
    pwm += 0.1f;
    if (pwm > 1.0f) {
        pwm = 1.0f;
    }
}

int main()
{
    r.mode(PullUp);
    g.mode(PullUp);
    b.mode(PullUp);

    // Use internal pullups for pushbutton
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    // Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    // Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();

    while(1) {
        myRGBled.write(!r*pwm,!g*pwm,!b*pwm);
    }
}

//End Part 3 ------------------------------------------
*/

/*
//Part 9 ----------------------------------------------

AnalogOut ao(p18);

float t = 0.0f;

int main()
{
    while(1){
        for (t = 0.0f; t < 6.3f; t += 0.314f) {
            ao = (sin(t) + 1.0f)/ (2.0f) ;
        }
    }
}

End Part 9 --------------------------------------------
*/