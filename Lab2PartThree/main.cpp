#include "mbed.h"
#include "uLCD_4DGL.h"
#include "SerialRPCInterface.h"

SerialRPCInterface RPC(USBTX, USBRX);
uLCD_4DGL uLCD(p9, p10, p11); // uLCD display

int main()
{
    Serial pc baud(9600); // Set the baud rate to match the terminal application


    while (1)
    {
        // Check if there is incoming data
        if (pc.readable())
        {
            // Read and display incoming ASCII data
            char c = pc.getc();
            uLCD.printf("%c", c);
        }
    }
}
