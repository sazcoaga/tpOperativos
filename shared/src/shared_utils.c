#include "shared_utils.h"

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error conectando \n");


	freeaddrinfo(server_info);

	return socket_cliente;

}

int crear_conexionServer(char *puerto, char * ip){

	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int listening_socket= socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	int optval = 1;
    setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

	if(bind(listening_socket, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error Linkenado puerto");

	if(listen(listening_socket,5) == -1)
		printf("error Listening");

	freeaddrinfo(server_info);

	return listening_socket;

}
