#include "Server.h"
#include <iostream>
#include <string>
#include <cstring>      //for memset
#include <sys/socket.h> //socket functions
#include <netdb.h>      //socket functions
#include <unistd.h> // socket close function
using namespace std;


Server::Server()
{
	status = 1;
}


Server::~Server()
{
}

int Server::isConnected()
{
	if (status == 0)
	{
		return true;
	}
	else
		return false;
}

void Server::restart()
{
	stop(); //close previous socket
	start();
}

bool Server::start()
{
	//struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	//struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

	memset(&host_info, 0, sizeof host_info);

	host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
	host_info.ai_socktype = SOCK_STREAM; //set up tcp
	host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

	    // Now fill up the linked list of host_info structs with google's address information.
	status = getaddrinfo(NULL, "1500", &host_info, &host_info_list);
	// getaddrinfo returns 0 on succes, or some other value when an error occured.
	// (translated into human readable text by the gai_gai_strerror function).
	if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status);


	//std::cout << "Creating a socket..."  << std::endl;
	socketfd = socket(host_info_list->ai_family,
		host_info_list->ai_socktype,
		host_info_list->ai_protocol);
	if (socketfd == -1)  std::cout << "socket error ";

	//std::cout << "Binding socket..."  << std::endl;
	// we use to make the setsockopt() function to make sure the port is not in use
	// by a previous execution of our code. (see man page for more information)
	int yes = 1;
	status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
	if (status == -1)  std::cout << "bind error" << std::endl;

	std::cout << "Listening for clients"  << std::endl;
	status =  listen(socketfd, 5);
	if (status == -1)  std::cout << "listen error" << std::endl;

	struct sockaddr_storage their_addr;
	socklen_t addr_size = sizeof(their_addr);
	new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
	if (new_sd == -1)
	{
		std::cout << "listen error" << std::endl;
	}
	else
	{
		//std::cout << "Connection accepted. Using new socketfd : "  <<  new_sd << std::endl;
		cout << "Connection accepted." << endl;
	}
}

string Server::Listen()
{
	std::cout << "Waiting to recieve data..."  << std::endl;
	ssize_t bytes_recieved;
	char incomming_data_buffer[1000];
	bytes_recieved = recv(new_sd, incomming_data_buffer, 1000, 0);
	// If no data arrives, the program will just wait here until some data arrives.
	if (bytes_recieved == 0)
	{
		//client disconnected
		status = 1;
	}
	if (bytes_recieved == -1)
		std::cout << "recieve error!" << std::endl;
	//cout << bytes_recieved << " bytes recieved :" << std::endl;
	incomming_data_buffer[bytes_recieved] = '\0';
	//std::cout << incomming_data_buffer << std::endl;
	return incomming_data_buffer;
}

void Server::stop()
{
	std::cout << "Stopping server..." << std::endl;
	freeaddrinfo(host_info_list);
	close(new_sd);
	close(socketfd);
}

void Server::reply(string response)
{
	cout << "sending " + response  << endl;
	ssize_t bytes_sent;
	if (bytes_sent = send(new_sd, response.c_str(), response.length(), 0) == -1) {
		cout << "sending msg failed" << endl;
	}		
}


