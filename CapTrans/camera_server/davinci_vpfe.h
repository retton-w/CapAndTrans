
/* davinci_vpfe.h */

#ifndef DAVINCI_VPFE_H
#define DAVINCI_VPFE_H

#define TRUE 1
#define FALSE 0

/* vpfe specific video standards */
#define VPFE_STD_625_50_SQP ((V4L2_STD_625_50)<<32)
#define VPFE_STD_525_60_SQP ((V4L2_STD_525_60)<<32)
#define VPFE_STD_AUTO ((v4l2_std_id)(0x1000000000000000ULL))
#define VPFE_STD_AUTO_SQP ((v4l2_std_id)(0x2000000000000000ULL))

#define VPFE_CMD_CONFIG_CCDC_YCBCR        _IOW('V',BASE_VIDIOC_PRIVATE +  1,  ccdc_params_ycbcr)
#define VPFE_CMD_LATEST_FRM_ONLY          _IOW('V',BASE_VIDIOC_PRIVATE +  2,  int)
#define VPFE_CMD_CONFIG_TVP5146           _IOW('V',BASE_VIDIOC_PRIVATE +  3,  tvp5146_params)
#define VPFE_CMD_CONFIG_CCDC_RAW          _IOW('V',BASE_VIDIOC_PRIVATE +  4,  ccdc_config_params_raw)
#define VPFE_CMD_S_MT9T001_PARAMS         _IOW('V',BASE_VIDIOC_PRIVATE +  5,  struct mt9t001_params)
#define VPFE_CMD_G_MT9T001_PARAMS         _IOR('V',BASE_VIDIOC_PRIVATE +  6,  struct mt9t001_params)
#define VPFE_CMD_SET_SENSOR_MODE_LIVE     _IOR('V',BASE_VIDIOC_PRIVATE +  7,  int)
#define VPFE_CMD_SET_SENSOR_MODE_TRIG     _IOR('V',BASE_VIDIOC_PRIVATE +  8,  int)
#define VPFE_CMD_SET_SENSOR_SHP           _IOW('V',BASE_VIDIOC_PRIVATE +  9,  int)
#define VPFE_CMD_SET_SENSOR_SHD           _IOW('V',BASE_VIDIOC_PRIVATE + 10,  int)
#define VPFE_CMD_SET_SENSOR_BLACK_LEVEL   _IOW('V',BASE_VIDIOC_PRIVATE + 11,  int)
#define VPFE_CMD_SET_SENSOR_ENABLE_FLASH  _IOW('V',BASE_VIDIOC_PRIVATE + 12,  int)
#define VPFE_CMD_SET_SENSOR_SELECT_8BIT   _IOW('V',BASE_VIDIOC_PRIVATE + 13,  int)
#define VPFE_CMD_SET_SENSOR_SELECT_10BIT  _IOW('V',BASE_VIDIOC_PRIVATE + 14,  int)
#define VPFE_CMD_SET_SENSOR_SET_RED_GAIN  _IOW('V',BASE_VIDIOC_PRIVATE + 15,  int)
#define VPFE_CMD_SET_SENSOR_SET_BLUE_GAIN _IOW('V',BASE_VIDIOC_PRIVATE + 16, int)
#define VPFE_CMD_SET_SENSOR_ENABLE_GAMMA  _IOW('V',BASE_VIDIOC_PRIVATE + 17,  int)
#define VPFE_CMD_SET_SENSOR_RESET         _IOW('V',BASE_VIDIOC_PRIVATE + 18,  int)
#define VPFE_CMD_ENABLE_VIDEO_PORT        _IOW('V',BASE_VIDIOC_PRIVATE + 19,  int)
#define VPFE_CMD_SET_SENSOR_SET_FLASH_DELAY _IOW('V',BASE_VIDIOC_PRIVATE + 20,  int)
#define VPFE_CMD_SET_SENSOR_SNAP_MODE     _IOW('V',BASE_VIDIOC_PRIVATE + 21,  int)
#define VPFE_CMD_SET_SENSOR_SNAP_INTERVAL _IOW('V',BASE_VIDIOC_PRIVATE + 22,  int)
#define VPFE_CMD_SET_SENSOR_ENABLE        _IOW('V',BASE_VIDIOC_PRIVATE + 23,  int)
#define VPFE_CMD_WRITE_DATA		  _IOW('V',BASE_VIDIOC_PRIVATE + 24,  int)
#define VPFE_CMD_READ_DATA        	  _IOWR('V',BASE_VIDIOC_PRIVATE + 25,  int)

/* Define for extra pixel/line and extra lines/frame */
#define NUM_EXTRAPIXELS		16
#define NUM_EXTRALINES		8

/* settings for commonly used video formats */
#define VPFE_WIN_NTSC    {0,0,720,480}
#define VPFE_WIN_PAL     {0,0,720,576}
#define VPFE_WIN_NTSC_SP {0,0,640,480}	/* ntsc square pixel */
#define VPFE_WIN_PAL_SP  {0,0,768,576}	/* pal square pixel */
#define VPFE_WIN_CIF     {0,0,352,288}
#define VPFE_WIN_QCIF    {0,0,176,144}
#define VPFE_WIN_QVGA    {0,0,320,240}
#define VPFE_WIN_SIF     {0,0,352,240}

#define VPFE_WIN_VGA	{0,0,(640 + NUM_EXTRAPIXELS),(480 + NUM_EXTRALINES)}
#define VPFE_WIN_SVGA 	{0,0,(800 + NUM_EXTRAPIXELS),(600 + NUM_EXTRALINES)}
#define VPFE_WIN_XGA	{0,0,(1024+ NUM_EXTRAPIXELS),(768 + NUM_EXTRALINES)}
#define VPFE_WIN_SXGA   {0,0,(1280+ NUM_EXTRAPIXELS),(1024+ NUM_EXTRALINES)}
#define VPFE_WIN_140W   {0,0,1392,1040}
#define VPFE_WIN_200W   {0,0,1628,1236}

        
#define VPFE_WIN_480p	{0,0,(720 + NUM_EXTRAPIXELS),(480 + NUM_EXTRALINES)}
#define VPFE_WIN_576p	{0,0,(720 + NUM_EXTRAPIXELS),(576 + NUM_EXTRALINES)}
#define VPFE_WIN_720p 	{0,0,(1280+ NUM_EXTRAPIXELS),(720 + NUM_EXTRALINES)}
#define VPFE_WIN_1080p 	{0,0,(1936),(1083)}

/* V4L2 defines added for new standards, 
					  these will be moved to videodev2.h */
#define V4L2_STD_MT9T001_VGA_30FPS	    (10)
#define V4L2_STD_MT9T001_VGA_60FPS	    (11)
#define V4L2_STD_MT9T001_SVGA_30FPS	    (12)
#define V4L2_STD_MT9T001_SVGA_60FPS	    (13)
#define V4L2_STD_MT9T001_XGA_30FPS	    (14)
#define V4L2_STD_MT9T001_SXGA_15FPS     (15)
#define V4L2_STD_MT9T001_480p_30FPS	    (17)
#define V4L2_STD_MT9T001_480p_60FPS	    (18)
#define V4L2_STD_MT9T001_576p_25FPS	    (19)
#define V4L2_STD_MT9T001_576p_50FPS	    (20)
#define V4L2_STD_MT9T001_720p_24FPS	    (21)
#define V4L2_STD_MT9T001_720p_30FPS	    (22)
#define V4L2_STD_MT9T001_1080p_18FPS	(23)
#define V4L2_STD_MT9T001_140W_15FPS     (16)
#define V4L2_STD_MT9T001_200W_15FPS     (24)

/* Define for device type to be passed in init */
#define 	MT9T001	0
#define		TVP5146	1
#define     CCD140W 2
#define 	MT9P031 3
#define     CCD200W 4

#ifdef __KERNEL__

#include <media/video-buf.h>

#define VPFE_MAJOR_RELEASE 0
#define VPFE_MINOR_RELEASE 0
#define VPFE_BUILD         1

#define VPFE_VERSION_CODE \
     (VPFE_MAJOR_RELEASE<<16)  | (VPFE_MINOR_RELEASE<<8) | VPFE_BUILD

/* By default, the driver is setup for auto-swich mode */
#define VPFE_DEFAULT_STD VPFE_STD_AUTO

#define VPFE_PIXELASPECT_NTSC 		{11, 10}
#define VPFE_PIXELASPECT_PAL  		{54, 59}
#define VPFE_PIXELASPECT_NTSC_SP    	{1, 1}
#define VPFE_PIXELASPECT_PAL_SP     	{1, 1}
#define VPFE_PIXELASPECT_DEFAULT    	{1, 1}

/* Buffer size defines for TVP5146 and MT9T001 */
#define VPFE_TVP5146_MAX_FRAME_WIDTH      768	/* for PAL Sqpixel mode */
#define VPFE_TVP5146_MAX_FRAME_HEIGHT     576	/* for PAL              */
/* 4:2:2 data */
#define VPFE_TVP5146_MAX_FBUF_SIZE      \
		 (VPFE_TVP5146_MAX_FRAME_WIDTH*VPFE_TVP5146_MAX_FRAME_HEIGHT*2)

#define VPFE_MT9T001_MAX_FRAME_WIDTH     (1936)
#define VPFE_MT9T001_MAX_FRAME_HEIGHT    (1083)
/* 2 BYTE FOR EACH PIXEL */
#define VPFE_MT9T001_MAX_FBUF_SIZE       \
		(VPFE_MT9T001_MAX_FRAME_WIDTH*VPFE_MT9T001_MAX_FRAME_HEIGHT*2)

/* frame buffers allocate at driver initialization time */
#define VPFE_DEFNUM_FBUFS             3

/* Defines for number of lines for all formats */
#define FMT_VGA_NUMLINES				(480 + NUM_EXTRALINES)
#define FMT_SVGA_NUMLINES				(600 + NUM_EXTRALINES)
#define FMT_XGA_NUMLINES				(768 + NUM_EXTRALINES)
#define FMT_SXGA_NUMLINES               (1024 + NUM_EXTRALINES)
#define FMT_480p_NUMLINES				(480 + NUM_EXTRALINES)
#define FMT_576p_NUMLINES				(576 + NUM_EXTRALINES)
#define FMT_720p_NUMLINES				(720 + NUM_EXTRALINES)
#define FMT_1080i_NUMLINES				(1083)

#define FMT_140W_NUMLINES               (1392)
#define FMT_200W_NUMLINES               (1628)

/* Defines for FPS values */
#define FPS_15_NUMERATOR				(1)
#define FPS_15_DENOMIRATOR				(15)
#define FPS_18_NUMERATOR				(1)
#define FPS_18_DENOMIRATOR				(18)
#define FPS_24_NUMERATOR				(1)
#define FPS_24_DENOMIRATOR  				(24)
#define FPS_25_NUMERATOR				(1)
#define FPS_25_DENOMIRATOR  				(25)
#define FPS_30_NUMERATOR				(1)
#define FPS_30_DENOMIRATOR  				(30)
#define FPS_50_NUMERATOR    				(1)
#define FPS_50_DENOMIRATOR  				(50)
#define FPS_60_NUMERATOR    				(1)
#define FPS_60_DENOMIRATOR  				(60)

#define FP_NUM_BYTES					(4)
/* Device configuration function pointer */
typedef int (*device_cfg_fxn) (unsigned int cmd, void *arg, void *params);

typedef struct vpfe_obj {
	struct video_device *video_dev;
	struct videobuf_queue bufqueue;	/* queue with frame buffers      */
	struct list_head dma_queue;
	u32 latest_only;	/* indicate whether to return the most */
	/* recent captured buffers only        */
	u32 usrs;
	u32 io_usrs;
	struct v4l2_prio_state prio;
	v4l2_std_id std;
	struct v4l2_rect vwin;
	struct v4l2_rect bounds;
	struct v4l2_fract pixelaspect;
	spinlock_t irqlock;
	struct semaphore lock;
	enum v4l2_field field;
	u32 pixelfmt;
	u32 numbuffers;
	u8 *fbuffers[VIDEO_MAX_FRAME];
	struct videobuf_buffer *curFrm;
	struct videobuf_buffer *nextFrm;
	int field_id;
	int mode_changed;
	int started;
	int field_offset;
	unsigned char capture_device;	/*set in vpfe_init()
					   (1=TVP5146, 0=MT9T001) */
	tvp5146_params tvp5146_params;
	void *device_params;	/*Pointer for video device. (MT9T001) */
	ccdc_params_raw ccdc_params_raw;	/*Object for CCDC raw mode */
	ccdc_params_ycbcr ccdc_params_ycbcr;	/*Object for CCDC ycbcr mode */
	device_cfg_fxn config_dev_fxn;	/*where,typedef int(*deviceCfg_Fxn)
					   (Uns cmd, void *arg, void *params); */

} vpfe_obj;

/* file handle */
typedef struct vpfe_fh {
	struct vpfe_obj *dev;
	int io_allowed;
	enum v4l2_priority prio;
} vpfe_fh;
#endif

#endif				/* DAVINCI_VPFE_H */
