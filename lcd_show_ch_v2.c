#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>




struct  fb_var_screeninfo  var;
struct  fb_fix_screeninfo  fix;

int main(int argc, const char *argv[])
{
	int  fd;

	fd =  open("/dev/fb0",O_RDWR);
	if(fd  <  0)
	{
	
		perror("fail   open fb0 ");
		exit(EXIT_SUCCESS);

	}

	ioctl(fd,FBIOGET_VSCREENINFO,&var);
	
	
	printf("xres  = %d\n",var.xres);
	printf("yres  = %d\n",var.yres);
	printf("xres_virtual  = %d\n",var.xres_virtual);
	printf("yres_virtual  = %d\n",var.yres_virtual);
	printf("xoffset  = %d\n",var.xoffset);
	printf("yoffset  = %d\n",var.yoffset);
	printf("bits_per_pixel  = %d\n",var.bits_per_pixel);


	ioctl(fd,FBIOGET_FSCREENINFO,&fix);
	printf("id  = %s\n",fix.id);
	printf("smem_start  = %ld\n",fix.smem_start);
	printf("smem_len  =  %d\n",fix.smem_len);


	return 0;
}
