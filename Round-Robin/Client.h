#pragma once
#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPSocket.h"

class Client{
    public:
        TCPSocket client_socket;

    private:

    public:
        Client(EthernetInterface * eth);
        ~Client(void);
        void send(char * next_hop_ip, int tcp_port, char data[]);

    private:
};
