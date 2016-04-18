#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>




struct  fb_var_screeninfo  var;
struct  fb_fix_screeninfo  fix;

unsigned int  line_width;
unsigned int  pixel_width;
int  screen_size;
unsigned char  *fbmem;

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



	line_width  = var.xres*var.bits_per_pixel/8;
	pixel_width  = var.bits_per_pixel/8;
    screen_size  = var.xres* var.yres *var.bits_per_pixel/8;

	fbmem  = mmap(NULL,screen_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(fbmem  <  0)
	{
	
		printf("cat not  mmap\n");
		exit(EXIT_FAILURE);
	}

	memset(fbmem,0x00ee00,screen_size);


	return 0;
}
