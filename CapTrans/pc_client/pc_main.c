#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#define REC_PORT    4617
#define MSG_PORT    6020
#define BUF_SIZE    1024
#define FILE_NAME   512

static pthread_t rec_tid;
static char *camera_ip = "192.168.3.99";

int connect_camera(struct sockaddr_in camera_addr, int sock, int camera_port)
{
	bzero(&camera_addr, sizeof camera_addr);
	camera_addr.sin_family = AF_INET;
	camera_addr.sin_port = htons(camera_port);
	inet_pton(AF_INET, camera_ip, &camera_addr.sin_addr);

	if (connect(sock, (struct sockaddr *)&camera_addr, sizeof camera_addr) < 0) {
		perror("Connect:");
		exit (1);
	}
	return 0;
}

void *rec_file(void *arg)
{
	struct sockaddr_in camera_addr;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket: ");
		exit (1);
	}
	connect_camera(camera_addr, sock, REC_PORT);

	//char file_name[FILE_NAME+1] = "/home/maple/image";

	char buf[BUF_SIZE];
	
	
	FILE *fp = fopen("/home/maple/image", "w");
	if (NULL == fp) {
		printf("open or create file  error!\n");
		exit (1);
	}
	
	bzero(buf, BUF_SIZE);
	int nread = 0;
	while ( nread = recv(sock, buf, BUF_SIZE, 0)) {
		if (nread < 0) {
			printf("In trans file pthread: rec data failed!\n");
			break;
		}
		int wread = fwrite(buf, sizeof (char), nread, fp);

		printf("writing!\n");
		if (wread < nread) {
			break;
		}
		bzero(buf, BUF_SIZE);
	}
	printf("FIle:  from camera[%s] rec over!\n", camera_ip);
	fclose(fp);
	close(sock);
	return NULL;
}

int main(void)
{
	struct sockaddr_in camera_addr2;
	int sock_talk = socket (AF_INET, SOCK_STREAM, 0);
	if (sock_talk < 0) {
		perror("In main socket:");
		exit (10);
	}
	connect_camera(camera_addr2, sock_talk, MSG_PORT);
	
	char buf[BUF_SIZE];
	bzero(buf, BUF_SIZE);
	while (1) {
		printf("If you want to capture one image, plz input command \"cap\"\n");
		printf("If you want to quit, plz input command \"exit\":\n");
		scanf("%s", buf);
		if ((strncmp(buf, "cap", 3) == 0) && send(sock_talk, buf, BUF_SIZE, 0)) {
			sleep(1);
			pthread_create(&rec_tid, NULL, (void *)rec_file, NULL); 
			pthread_join(rec_tid, NULL);
		}
		else if(strncmp(buf, "exit", 4) == 0) {
			break;
		}
		else {
			printf("error\n");
			continue;
		}
	}	
	return 0;
}
