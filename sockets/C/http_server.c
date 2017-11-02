#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sockets Libraries API
#include <sys/types.h>
#include <sys/socket.h>


#include <netinet/in.h>


int main(int argc, char const *argv[]) {
	// open a file to server
	FILE *html_data;
	html_data = fopen("index.html", "r");

	char response_data[1024];
	fgets(response_data, 1024, html_data);

	char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
	strcat(http_header, response_data);

	// creating the socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);


	// define the address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8001);
	server_address.sin_addr.s_addr = INADDR_ANY;


	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 5);
	

	int client_socket;
	while(1) {
		client_socket = accept(server_socket, NULL, NULL);

		// send the message to the client socket
		send(client_socket, http_header, sizeof(http_header), 0);

		// close the socket
		close(client_socket);

	}



	return 0;
}