#include "mbed.h"
#include "PinDetect.h"
//See http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html
//for a detailed explanation of the RPG encoder counting algorithm
//uses Sparkfun RPG with RGB led on breakout board (#15141,11722,10597)
//place RPG PCB across a breadboard power bus strip for easier pin hookup!
InterruptIn RPG_A(p14,PullUp);//encoder A and B pins/bits use interrupts
InterruptIn RPG_B(p15,PullUp);
PinDetect RPG_PB(p16); //encode pushbutton switch "SW" on PCB
//PWM setup for RGB LED in enocder
PwmOut red(p21);//"R" pin
PwmOut blue(p22);//"G" pin
PwmOut green(p23);//"B" pin
//Note: also tie RPG PCB "C" pin to ground, "+" pin to 3.3
//mbed status leds
DigitalOut ledPB(LED1);
DigitalOut red_adjust_mode(LED2);
DigitalOut green_adjust_mode(LED3);
DigitalOut blue_adjust_mode(LED4);
//Serial pc(USBTX,USBRX);
volatile int old_enc = 0;
volatile int new_enc = 0;
volatile int enc_count = 0;
//Instead of a slow 16 case statement use a faster table lookup of truth table
//index table with (previous encoder AB value<<2 | current current encoder AB value) 
//to find -1(CCW),0,or 1(CW) change in count each time a bit changes state
//Always want Interrupt routines to run fast!
//const puts data in read only Flash instead of RAM
const int lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
//Encoder bit change interrupt service routine
//called whenever one of the two A,B encoder bits change state
void Enc_change_ISR(void)
{
    new_enc = RPG_A<<1 | RPG_B;//current encoder bits
    //check truth table for -1,0 or +1 added to count
    enc_count = enc_count + lookup_table[old_enc<<2 | new_enc];
    old_enc = new_enc;
}
//debounced RPG pushbutton switch callback
void PB_callback(void)
{
    ledPB= !ledPB;
}
int main()
{
//turn off built-in RPG encoder RGB led
    red = 1.0;//PWM value 1.0 is "off", 0.0 is full "on"
    green = 1.0;
    blue = 1.0;
//current color adjust set to red
    red_adjust_mode = 1;
//debounce RPG center pushbutton
    RPG_PB.mode(PullDown);
    RPG_PB.attach_deasserted(&PB_callback);
    RPG_PB.setSampleFrequency();
// generate an interrupt on any change in either encoder bit (A or B)
    RPG_A.rise(&Enc_change_ISR);
    RPG_A.fall(&Enc_change_ISR);
    RPG_B.rise(&Enc_change_ISR);
    RPG_B.fall(&Enc_change_ISR);
    while (true) {
        // Scale/limit count to 0..100
        if (enc_count>100) enc_count = 100;
        if (enc_count<0) enc_count = 0;
        red = 1.0 - enc_count/100.0;
//        pc.printf("%D\n\r",enc_count);
    }
}
