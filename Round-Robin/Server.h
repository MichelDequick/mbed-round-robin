#pragma once
#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPServer.h"
#include "TCPSocket.h"

class Server{
    public:
        TCPServer server;
        TCPSocket server_socket;

    private:

    public:
        Server(EthernetInterface * eth, int tcp_port);
        ~Server(void);
        void recieve(char * data);

    private:
};
