#ifndef _CAMERA_H
#define _CAMERA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <netinet/in.h>
#include <linux/videodev2.h>

#define MSG_PORT   	6020
#define SEND_PORT	4617
#define BUF_SIZE	1024

#define CLEAR(x) memset(&(x), 0, sizeof (x))

#define SUCCESS 0
#define FAILURE 1

#define TRUE 	1
#define FALSE	0


extern void errno_exit(const char *);

extern int xioctl(int, int, void *);

extern void *thread_capture(void *);

extern void *send_file(void *);

#endif
