#include<BitMapManager.h>
#include<string.h>
#include<stdio.h>
#include<DisplayManager.h>

static PT_BipMapOperation g_PTBitMapInstanceHead;

int RegisterBipMap(PT_BipMapOperation pt_BipMapOperation)
{
    if(!g_PTBitMapInstanceHead)
    {
        g_PTBitMapInstanceHead = pt_BipMapOperation;
        g_PTBitMapInstanceHead->PTNext = NULL;
    }
    else
    {
        PT_BipMapOperation pt_PTBitMapInstanceTemp = g_PTBitMapInstanceHead;
        while(pt_PTBitMapInstanceTemp->PTNext)
        {
            pt_PTBitMapInstanceTemp = pt_PTBitMapInstanceTemp->PTNext;
        }
        pt_PTBitMapInstanceTemp->PTNext = pt_BipMapOperation;
        pt_BipMapOperation->PTNext = NULL;
       
    }
     return 0;
}
int BitMapInstanceInit()
{
   int ret = FreeTypeInstanceInit();
   if(ret)
   {
    printf("BitMapInstanceInit Error !\n");
   }
   return ret;
}

int BitMapFreetypeInit(char* filePathName,int fontSize)
{
     PT_BipMapOperation pt_PTBitMapInstanceTemp = g_PTBitMapInstanceHead;
     while(pt_PTBitMapInstanceTemp)
     {
        if(strcmp(pt_PTBitMapInstanceTemp->Name,"freetype")==0)
        {
            pt_PTBitMapInstanceTemp->InitBitMap(filePathName, fontSize);
            return 0;
        }
        
     }
     return -1;
}

PT_BipMapOperation GetBipMapInstanceByName(char* name)
{
     PT_BipMapOperation pt_PTBitMapInstanceTemp = g_PTBitMapInstanceHead;
     while(pt_PTBitMapInstanceTemp)
     {
        if(strcmp(pt_PTBitMapInstanceTemp->Name,name)==0)
        {
            return pt_PTBitMapInstanceTemp;
        }
       pt_PTBitMapInstanceTemp = pt_PTBitMapInstanceTemp->PTNext; 
     }
     return NULL;
}
int TestBitMapManager(char* filePath , int size)
{
    
    char* s = "AABBCCCCCC";
    PT_DispOpr pt_DispOpr;
    PT_BipMapOperation pt_BipMapOperation;
    DisplayInstancesInit();
    BitMapInstanceInit();

    DisplayTextInit();
    BitMapFreetypeInit(filePath,size);

    pt_DispOpr = GetDisplayInstanceByName("fb");
    pt_BipMapOperation = GetBipMapInstanceByName("freetype");
    FT_BBox  abbox ;
    int len = strlen(s);
    
    int offX = 0;
    for(int i =0 ;i<len;i++)
    {   
      FT_Bitmap bitMap =  pt_BipMapOperation->GetABitMap(&s[i],&abbox);
      pt_DispOpr->ShowingBitmap(&bitMap,offX,20);
      offX+=abbox.xMax;

    }
    return 0;
}
