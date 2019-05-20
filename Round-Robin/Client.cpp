#include "Client.h"
#include "mbed.h"

Client::Client(EthernetInterface * eth)
{ 
    client_socket.open(eth);
}

Client::~Client(void)
{

}

void Client::send(char * next_hop_ip, int tcp_port, char data[])
{
    client_socket.connect(next_hop_ip, tcp_port);
    nsapi_size_t size = strlen(data);
    client_socket.send(data, size);
    client_socket.close();
}
