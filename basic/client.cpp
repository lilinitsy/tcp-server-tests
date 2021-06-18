#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdexcept>

#define PORT 1234

int main()
{
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		throw std::runtime_error("Could not create a socket");
	}

	sockaddr_in server_address = {
		.sin_family = AF_INET,
		.sin_port = PORT,
	};

	int connect_result = connect(socket_fd, (sockaddr*) &server_address, sizeof(server_address));
	if(connect_result == -1)
	{
		throw std::runtime_error("Could not connect to server");
	}

	char packet_to_send[1024];
	char servbuf[1024];

	while(1)
	{
		int bytes_to_send = read(STDIN_FILENO, packet_to_send, 1024);

		if(!bytes_to_send)
		{
			break;
		}

		write(socket_fd, packet_to_send, bytes_to_send);

		int server_read = read(socket_fd, servbuf, 1024);
		printf("Message from server: %s\n", servbuf);
	}

	/*send(socket_fd, "fuck", 4, 0);
	printf("msg sent\n");
	
	char servbuf[1024];
	int server_read = read(socket_fd, servbuf, 1024);
	printf("Message from server: %s\n", servbuf);*/

	return 0;
}