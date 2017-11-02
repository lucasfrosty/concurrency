#include <stdio.h>
#include <stdlib.h>

// Sockets Libraries API
#include <sys/types.h>
#include <sys/socket.h>


#include <netinet/in.h>

int main(int argc, char const *argv[])
{
	char server_message[256] = "You've reached the server!";

	// create the server;
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);


	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	// recieve the data of the client socket
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// send the message to the client socket
	send(client_socket, server_message, sizeof(server_message), 0);

	// close the socket
	close(server_socket);

	return 0;
}