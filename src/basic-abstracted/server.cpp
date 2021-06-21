#include <netinet/in.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 1234


struct Server
{
	int socket_fd;
	int client_fd;

	Server()
	{
		// Create socket
		socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(socket_fd == 0)
		{
			throw std::runtime_error("Socket creation failed");
		}
	}

	void connect_to_client(int port)
	{

		// define the address struct to be for TCP using this port
		sockaddr_in address = {
			.sin_family = AF_INET,
			.sin_port	= static_cast<in_port_t>(port),
		};

		// bind to socket
		int binding = bind(socket_fd, (sockaddr *) &address, sizeof(address));
		if(binding == -1)
		{
			throw std::runtime_error("Bind to socket failed");
		}

		// Listen for a client to connect
		listen(socket_fd, 1);
		// Accept a connection from a client
		client_fd = accept(socket_fd, nullptr, nullptr);
	}

	void run()
	{
		// loop de loop
		while(1)
		{
			if(client_fd != -1)
			{
				printf("Client accepted\n");
			}

			// Read the client's message
			char clientbuf[1024];
			int client_read = read(client_fd, clientbuf, 1024);
			printf("Message from client: %s\n", clientbuf);

			// Send a message to the client
			send(client_fd, "tstmsg", 6, 0);
			printf("message sent to client\n");
		}
	}
};


int main()
{
	Server server = Server();
	server.connect_to_client(PORT);
	server.run();

	return 0;
}