#ifndef _DISPLAYMANAGER_H
#define _DISPLAYMANAGER_H

#define FBDEVICEPATH "/dev/fb0"
typedef struct DisplayOperation
{
    char* Name;
    void (*Showing)(int x, int y, unsigned int color);
    int (*InitDisplay)();
    struct DisplayOperation* PTNext;
} T_DispOpr, *PT_DispOpr;

int DisplayInstancesInit();
int FBInstanceInit();
int RegisterDisplayDev(PT_DispOpr pt_DispOpr);
int DisplayTextInit();
PT_DispOpr GetDisplayInstanceByName(char* name);
int TestDisplay();
#endif