#pragma once
#include <sys/socket.h> //socket functions
#include <netdb.h>      //socket functions
#include <string>
using namespace std;
class Server
{
public:
	Server();
	~Server();
	string Listen();
	int isConnected();
	bool start();
	void stop();
	void restart();
	void reply(string response);
	
private:
	int status, new_sd, socketfd; // The socket descripter
	struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
};

