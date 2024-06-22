#include<DisplayManager.h>
#include<string.h>
#include<stdio.h>
static PT_DispOpr g_PTInstanceHead; 

/*
    using head insert to manage different display device instance
*/
int RegisterDisplayDev(PT_DispOpr pt_DispOpr)
{
    if(!g_PTInstanceHead)
    {
        g_PTInstanceHead = pt_DispOpr;
        g_PTInstanceHead->PTNext = NULL;
    }
    else
    {
        PT_DispOpr pt_PTInstance_temp =  g_PTInstanceHead;
        while(pt_PTInstance_temp->PTNext)
        {
            pt_PTInstance_temp = pt_PTInstance_temp->PTNext;
        }
        pt_PTInstance_temp->PTNext = pt_DispOpr;
        pt_DispOpr->PTNext = NULL;
       
    }
     return 0;
}

int DisplayInstancesInit()
{
    int ret = FBInstanceInit();
    if(ret)
    {
        printf("FB Device init error!\n");
        return -1;
    }
    return 0;
}

int DisplayTextInit()
{
    PT_DispOpr pt_PTInstance_temp = g_PTInstanceHead;
    while(pt_PTInstance_temp)
    {
       int ret =  pt_PTInstance_temp->InitDisplay();
       if(ret)
       {
        printf("%s DisplayTextInit error!\n",pt_PTInstance_temp->Name);
        return -1 ;
       }
        pt_PTInstance_temp = pt_PTInstance_temp->PTNext;
    }
    return 0;
}

PT_DispOpr GetDisplayInstanceByName(char* name)
{
     PT_DispOpr pt_PTInstance_temp = g_PTInstanceHead;
     while(pt_PTInstance_temp)
     {
        if(strcmp(pt_PTInstance_temp->Name,name)==0)
        return pt_PTInstance_temp;
     }
     return NULL;
}

int TestDisplay()
{
    DisplayInstancesInit();// to get different display device instances
    DisplayTextInit(); // display device instances should be initialed
    PT_DispOpr myDisplayDevice = GetDisplayInstanceByName("fb");
    for (int i = 0; i < 100; i++) 
    {
        for (int j = 0; j < 100; j++) 
        {
        myDisplayDevice->Showing(100 + i, 100 + j, 0xff);
        }
    }
     return 0;
}


