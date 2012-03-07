#include <linux/videodev2.h>
#include "davinci_vpfe.h"
#include "ccdc_davinci.h"
#include "sensor.h"

#include "camera.h"


#define MIN_CAPTURE_BUFFER 3

struct buffer {
	void * 	start;
	int 	length;
};

struct buffer *buffers;

unsigned int n_buffers = 0;

static int fdCapture = -1;

const char *dev_name = "/dev/video0";

static inline int query_capability(int fd)
{
	struct v4l2_capability cap;

	if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap))
		errno_exit("VIDIOC_QUERYCAP");
	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
		fprintf(stderr, "Capture is not supported!\n");
		return -1;
	}
	if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
		fprintf(stderr, "Steaming io not supported!\n");
		return -1;
	}
	return 0;
}
	
static inline int set_format(int fd)
{
	v4l2_std_id std = V4L2_STD_NTSC;
	struct v4l2_format fmt;

	if (-1 == xioctl(fd, VIDIOC_S_STD, &std))
		errno_exit("VIDIOC_S_STD");
	sleep(1);

	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width	= 640;
	fmt.fmt.pix.height	= 480;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8;
	fmt.fmt.pix.field	= V4L2_FIELD_NONE;
	
	if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
		errno_exit("VIDIOC_S_FMT");
	return 0;
}


static inline int config_ccdc(int fd)
{
	ccdc_config_params_raw raw_params = {
		.fid_pol = CCDC_PINPOL_POSITIVE,
		.vd_pol  = CCDC_PINPOL_POSITIVE,
		.hd_pol  = CCDC_PINPOL_POSITIVE,
		.image_invert_enable = FALSE,
		.alaw = {
			.b_alaw_enable = FALSE,
		},
		.blk_clamp = {
			.b_clamp_enable = FALSE,
			.dc_sub = 0,
		},
		.blk_comp = {0, 0, 0, 0},
		.fault_pxl = {
			.fpc_enable = FALSE,
		},
	};
	raw_params.data_sz = _8BITS;

	if (-1 == xioctl(fd, VPFE_CMD_CONFIG_CCDC_RAW, &raw_params))
		errno_exit("VPFE_CMD_CONFIG_CCDC_RAW");	
	return 0;
}

static inline int init_buffer(int fd)
{
	struct v4l2_requestbuffers req;
	CLEAR(req);

	req.count   = MIN_CAPTURE_BUFFER;
	req.type    = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory  = V4L2_MEMORY_MMAP;
	
	if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
		if (EINVAL == errno) {
			fprintf(stderr, "%s does not support mmap\n", dev_name);
			exit (EXIT_FAILURE);
		}
		else
			errno_exit("VIDIOC_REQBUFS");
	}

	if (req.count < MIN_CAPTURE_BUFFER) {
		fprintf(stderr, "buffers req failure!\n");
		return -1;
	}
	
	buffers = calloc(req.count, sizeof (*buffers));
	if (!buffers) {
		fprintf(stderr, "Out of memory\n");
		return -1;
	}

	for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
		struct v4l2_buffer buf;
		CLEAR(buf);
	
		buf.type 	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory 	= V4L2_MEMORY_MMAP;
		buf.index	= n_buffers;

		if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf)) 
			errno_exit("VIDIOC_QUERYBUF");
		buffers[n_buffers].length = buf.length;
		buffers[n_buffers].start  = mmap(NULL, buf.length, PROT_READ |
				PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
		if (MAP_FAILED == buffers[n_buffers].start)
			errno_exit("mmap");
		if (-1 == xioctl(fd , VIDIOC_QBUF, &buf))
			errno_exit("VIDIOC_QUERYBUF");
	}

	return 0;
} 

static inline int start(int fd)
{
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	
	if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
		errno_exit("VIDIOC_STREAMON");
	return 0;
}

static inline int init_device(void)
{
	int fd = -1;

	if ((fd = open(dev_name, O_RDWR | O_NONBLOCK, 0)) <= 0) {
		perror("Open device");
		goto ret_open;
	}
	
	int temp;
	if (-1 == xioctl(fd, VPFE_CMD_SET_SENSOR_RESET, &temp))
		errno_exit("VPFE_CMD_SET_SENSOR_RESET");

	int type;
	if (-1 == xioctl(fd, VPFE_CMD_SET_SENSOR_MODE_LIVE, &type))
		errno_exit("VPFE_CMD_SET_SENSOR_MODE_LIVE");

	int arg = 1;
	if (-1 == xioctl(fd, VPFE_CMD_SET_SENSOR_ENABLE, &arg))
		errno_exit("VPFE_CMD_SET_SENSOR_ENABLE");	

	if (query_capability(fd) < 0) 
		goto ret_query_capability;

	if (set_format(fd) < 0)
		goto ret_set_format;

	if (config_ccdc(fd) < 0)
		goto ret_config_ccdc;
	
	if (init_buffer(fd) < 0)
		goto ret_init_buffer;

	if (start(fd) < 0) 
		goto ret_start;
	fdCapture = fd;
	return fd;

ret_start:
ret_init_buffer:
ret_config_ccdc:
ret_set_format:
ret_query_capability:
	close (fd);
	fd = -1;
ret_open:
	return fd;
}

static inline void deinit_device(int fd)
{
	if (fd < 0) {
		return ;
	}
	int i;
	enum v4l2_buf_type type;
	if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
		errno_exit("VIDIOC_STREAMOFF");

	for (i = 0; i < n_buffers; i++)
		munmap(buffers[i].start, buffers[i].length);

	close (fd);
}

void *thread_capture(void *arg)
{

	int fd			= -1;
	struct v4l2_buffer v4l2buf;

	if ((fd = init_device()) <= 0)
		exit(-1);
	
	int count = 100;
	while (1) {
		usleep(20000);
		
		CLEAR(v4l2buf);
		v4l2buf.type	= V4L2_BUF_TYPE_VIDEO_CAPTURE;
		v4l2buf.memory	= V4L2_MEMORY_MMAP;

		printf("capture thread\n");
		
		if (-1 == xioctl(fd, VIDIOC_DQBUF, &v4l2buf)) {
			if (EAGAIN == errno) {
				fprintf(stderr, "DQBUF error: EAGAIN\n");
				continue;
			}
			if (EINTR == errno) {
				fprintf(stderr, "DQBUF error: EINTR\n");
				continue;
			}
			fprintf(stderr, "capture thread failure!\n");
		}
		printf("after DQBUF\n");
		
		char *file_name  = "/data/app/image.raw";
		int ffd = open(file_name, O_RDWR | O_CREAT);

	
		write(ffd, buffers[v4l2buf.index].start, v4l2buf.length);
		if (-1 == xioctl(fd, VIDIOC_QBUF, &v4l2buf))
			errno_exit("VIDIOC_QBUF");
		close(ffd);
		printf("capture one image!\n");
		break;
	}

	deinit_device(fd);
	return NULL;
}
