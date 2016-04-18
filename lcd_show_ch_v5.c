#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include "font.h"




struct  fb_var_screeninfo  var;
struct  fb_fix_screeninfo  fix;

unsigned int  line_width;
unsigned int  pixel_width;
int  screen_size;
unsigned char  *fbmem;

void lcd_put_pixel(int x,int  y,unsigned int   color)
{

	unsigned  char  * pen8  =  fbmem+y*line_width+x*pixel_width;
	unsigned short *pen16;
	pen16  = (unsigned  short  *)pen8;
	unsigned int red,green,blue;
	switch(var.bits_per_pixel)
	{
	
	case 16:
		red  = (color >>16) & 0xff;
		green = (color >>8)& 0xff;
		blue  = (color >>0)*0xff;
		color  = ((red >>3)<<11|(green >>2)<<5|(blue >>3));
		*pen16  = color;

		break;

	}

}

void  lcd_put_ascii(int x,int y,unsigned char c)
{

	unsigned  char  * dots  =  (unsigned char  *)&fontdata_8x16[c*16] ;
	int  i,b;
	unsigned  char  byte;

	for(i  =0  ;  i<  16;i++)
	{
	
		byte  =  dots[i];
		for(b = 7; b  >=0;b --)
		{
			if(byte  &(1 <<b))
			{
			
				lcd_put_pixel(x+7-b,y+i,0xffffff);
			
			}
			else
				lcd_put_pixel(x+7-b,y+i,0);
		}
	}


}
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

	memset(fbmem,0,screen_size);

	lcd_put_ascii(var.xres/2,var.yres/2,'A');


	return 0;
}
