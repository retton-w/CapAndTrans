#include "camera.h"
void *send_file(void *arg)
{
	struct sockaddr_in server_addr;
	int sock;
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) 
		errno_exit("socket");
	bzero (&server_addr, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(SEND_PORT);
	
	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof server_addr) < 0) 
		errno_exit("bind");

	if (listen(server_socket, 5) < 0) 
		errno_exit("listen");
	int i;

	while (1) {
		printf("In pthread send file!\n");
		struct sockaddr_in client_addr;
		socklen_t client_addr_len;
		sock = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
		if (sock < 0)
			errno_exit("sock");
		printf("send sock\n");

		char *file_name = "/data/app/image.raw";
		FILE *fp = fopen(file_name, "r");
		char buf[BUF_SIZE];
		bzero(buf, BUF_SIZE);
		int nread = 0;
		while(1) {
			nread = fread(buf, sizeof(char), BUF_SIZE, fp);
			if (nread > 0) {
				if (send(sock, buf, nread, 0) < 0) {
					printf("send error!\n");
					break;
				}
			}
			else 
				break;
				
			bzero(buf, BUF_SIZE);
			printf("sending !\n");
		}
		fclose(fp);
	
		printf("trans over!\n");
		break;
	}
	return NULL;
}

