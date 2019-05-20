#include "Server.h"
#include "mbed.h"

Server::Server(EthernetInterface * eth, int tcp_port) : server(eth)
{ 
    server.bind(tcp_port);
    server.set_blocking(true);
    server.listen(1);
}

Server::~Server(void)
{

}

void Server::recieve( char * data)
{
    memset(data, 0x0, 256);
    server.accept(&server_socket); // Will wait here until incoming connection is established
    server_socket.recv(data, 256);
    server_socket.close();
}
