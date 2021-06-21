#include <arpa/inet.h>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 1234


struct Client
{
	int socket_fd;

	Client()
	{
		socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(socket_fd == -1)
		{
			throw std::runtime_error("Could not create a socket");
		}
	}

	void connect_to_server(int port)
	{
		sockaddr_in server_address = {
			.sin_family = AF_INET,
			.sin_port	= static_cast<in_port_t>(port),
		};


		int connect_result = connect(socket_fd, (sockaddr *) &server_address, sizeof(server_address));
		if(connect_result == -1)
		{
			throw std::runtime_error("Could not connect to server");
		}
	}

	void run()
	{
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
	}
};




int main()
{
	Client client = Client();
	client.connect_to_server(PORT);
	client.run();


	return 0;
}