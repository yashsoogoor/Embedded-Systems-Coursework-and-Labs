#include "mbed.h"
#include "EthernetInterface.h"
BusOut leds(LED1,LED2,LED3,LED4); //LEDs are controlled by web page text data
// Network interface
EthernetInterface net;

// Socket demo
int main()
{
    // Show MAC in case it is needed to enable DHCP on a secure network
    char mac[6];
    mbed_mac_address(mac);
    printf("\r\rmbed's MAC address is %02x:%02x:%02x:%02x:%02x:%02x\n\r", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    // Bring up the ethernet interface
    printf("Waiting for IP address from DHCP Server\n\r");
    wait(1.0);
    net.connect();
    printf("\n\rEthernet socket example\n\r");

    // Show the network address
    const char *ip = net.get_ip_address();
    printf("IP address is: %s\n\r", ip ? ip : "Timeout - No IP obtained");

    // Open a socket on the network interface, and create a TCP connection to mbed.org
    TCPSocket socket;
    socket.open(&net);
    socket.connect("hamblen.ece.gatech.edu", 80);

    // Send a simple http request
    char sbuffer[] = "GET /hello.txt HTTP/1.1\r\nHost: hamblen.ece.gatech.edu\r\n\r\n";
    int scount = socket.send(sbuffer, sizeof sbuffer);
    //print out packet
    printf("sent %d [%.*s]\n\r", scount, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);

    // Recieve a simple http response and print out the response line and text
    char rbuffer[400]; //enough for a very short text page - almost out of RAM!
    int rcount = socket.recv(rbuffer, sizeof rbuffer);
    rbuffer[rcount] = 0; //terminate to print as a C string;
    //Print packet read from HTTP web page server
    printf("recv %d [%.*s]\n\r", rcount, strstr(rbuffer, "\r\n"), rbuffer);

    // Close the socket to return its memory and bring down the network interface
    socket.close();

    // Basic IoT demo controlling mbeds 4 LEDs from Internet web page's ASCII text data
    // Web page demo contains a line "Data:0101"
    char *data;
    data = strstr(rbuffer,"Data:"); //Find Data: line on web page with '0's or '1's
    data = data + 5; //Skip to data
    for (int i=0; i<=3; i++) //Parse 4 web page characters to control LEDs
        leds[i] = data[i] - '0'; //convert ASCII '0' or '1's to binary to control 4 leds
    //Another device could change the web page contents to control LEDs from anywhere

    // Bring down the ethernet interface
    net.disconnect();
    printf("Done\n\r");
}
