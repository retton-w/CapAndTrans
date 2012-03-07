#include "camera.h"

//extern int pipes[2];

static pthread_t trans_tid;
static pthread_t capture_tid;

int main(void)
{
	
	struct sockaddr_in camera_addr, pc_addr;
	socklen_t pc_addr_len;
	int listenfd, msg_sock;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) 
		errno_exit("main thread, socket");

	bzero(&camera_addr, sizeof camera_addr);
	camera_addr.sin_family = AF_INET;
	camera_addr.sin_addr.s_addr = htons(INADDR_ANY);
	camera_addr.sin_port = htons(MSG_PORT);
	if (bind(listenfd, (struct sockaddr *)&camera_addr, sizeof camera_addr) < 0) 
		errno_exit("main thread, bind");
	if (listen(listenfd, 5) < 0) 
		errno_exit("main thread, listen");
	printf("listening .....\n");
	while (1) {
		pc_addr_len = sizeof(pc_addr);
		msg_sock = accept(listenfd, (struct sockaddr *)&pc_addr, &pc_addr_len);
		char buf[BUF_SIZE];
		while (1) {
			bzero(buf, BUF_SIZE);
			recv(msg_sock, buf, BUF_SIZE, 0);	
			if (!strncmp(buf, "cap", 3)) {
				printf("ready to capturing...\n");
				pthread_create(&capture_tid, NULL, (void *)thread_capture, NULL);
				pthread_join(capture_tid, NULL);
				pthread_create(&trans_tid, NULL, (void *)send_file, NULL);
				pthread_join(trans_tid, NULL);
				goto ret;
			}
			else
				continue;
		}
	}
ret:
	return 0;
}	

void errno_exit(const char *s)
{
	fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
	exit (EXIT_FAILURE);
}

int xioctl(int fd, int request, void *arg)
{
	int r;
	do r = ioctl(fd, request, arg);
	while (-1 == r && EINTR == errno);
	return r;
}

	

	
	
