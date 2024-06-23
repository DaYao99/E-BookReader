#ifndef BITMAPMANAGER_H
#define BITMAPMANAGER_H  
#include <ft2build.h>
#include FT_GLYPH_H 
#include FT_FREETYPE_H
typedef struct BipMapOperation
{
    char* Name;
    FT_Bitmap (*GetABitMap)(char* data,FT_BBox* abbox);
    int (*InitBitMap)(char* filePathName,int fontSize);
    struct BipMapOperation* PTNext;
} T_BipMapOperation, *PT_BipMapOperation;

int RegisterBipMap(PT_BipMapOperation pt_BipMapOperation);
int FreeTypeInstanceInit();
int BitMapFreetypeInit(char* filePathName,int fontSize);
int BitMapAsciiInit(char* filePathName,int fontSize);
int BitMapInstanceInit();
PT_BipMapOperation GetBipMapInstanceByName(char* name);
int TestBitMapManager(char* filePath , int size);
#endif