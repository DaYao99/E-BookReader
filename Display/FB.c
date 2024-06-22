#include <DisplayManager.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <stdio.h>
static void FBShowPix(int x, int y, unsigned int color);
static int FBInit();
static unsigned char* FBAddress;
static struct fb_var_screeninfo VarInfo;
static struct fb_fix_screeninfo FixInfo;
static int ScreenWidth ;
static int PIXWidth ;
static T_DispOpr g_fb =
{
    .Name = "fb",
    .Showing = FBShowPix,
    .InitDisplay = FBInit,
};

static int FBInit()
{
    
    int fd = open(FBDEVICEPATH , O_RDWR);
    if (fd < 0)
    {
        printf("FBInit Error!\n");
        return -1;
    }
    ioctl(fd, FBIOGET_VSCREENINFO, &VarInfo);
    ioctl(fd, FBIOGET_FSCREENINFO, &FixInfo);
    ScreenWidth = VarInfo.xres*VarInfo.bits_per_pixel /8;
    PIXWidth = VarInfo.bits_per_pixel /8;
    int size = VarInfo.xres * VarInfo.yres * VarInfo.bits_per_pixel /8;
    FBAddress = mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    if(!FBAddress)
    {
        printf("FBAddress mmap error!\n");
    }
    
    return 0;

}

static void FBShowPix(int x, int y, unsigned int color)
{
    unsigned char* data8 = FBAddress + y*ScreenWidth + x*PIXWidth;
    short unsigned int* data16 =(short unsigned int*)data8;
    unsigned int* data32 = (unsigned int*)data8;
    switch(VarInfo.bits_per_pixel)
    {
        case 8:
            *data8 = color ;
            break;
        case 16:
            {
                int red = (color >> 16) & (0xff);
                int green = (color >> 8) & (0xff);
                int blue =  color & (0xff);
                *data16 = ((red>>3)<<11) | ((green >> 2) << 5) | (blue >> 3);
            break;
            }
        case 32:
            *data32 = color;
            break;
    }
}

int FBInstanceInit()
{
  return RegisterDisplayDev(&g_fb);
}