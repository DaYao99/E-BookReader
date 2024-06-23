#include <BitMapManager.h>


static int FreeTypeInit(char* filePathName,int fontSize);
static FT_Bitmap GetAFreeTypeBitMap( char* data,FT_BBox* bbox);
FT_Library    g_pFTLib        =  NULL;
FT_Face       g_pFTFace       =  NULL;
static T_BipMapOperation g_bit_map =
{
    .Name = "freetype",
    .InitBitMap = FreeTypeInit,
    .GetABitMap = GetAFreeTypeBitMap,
};

int FreeTypeInstanceInit()
{
  return  RegisterBipMap(&g_bit_map);
}


static int FreeTypeInit(char* filePathName,int fontSize )
{
   //Init FreeType Lib to manage memory
    int ret = FT_Init_FreeType( &g_pFTLib);
    if (ret)
    {
        printf( "Init FreeType Library Error!\n");
        return  - 1 ;
    }
    

    ret =  FT_New_Face(g_pFTLib, filePathName, 0, &g_pFTFace);
    if(ret)
    {
        printf( " FreeType FT_New_Face Error!\n");
        return  - 1 ;
    }
   
    FT_Set_Pixel_Sizes(g_pFTFace, 0, fontSize ); 
    return 0;
    
}
static FT_Bitmap GetAFreeTypeBitMap( char* data,FT_BBox* bbox)
{
    int ret = FT_Load_Char( g_pFTFace, *data, FT_LOAD_RENDER );
    FT_GlyphSlot  slot;
    FT_BBox temp_bbox;
    temp_bbox.xMax = INT_MIN;
    temp_bbox.yMax = INT_MIN;
    temp_bbox.xMin = INT_MAX;
    temp_bbox.yMin = INT_MAX;
    slot = g_pFTFace->glyph;
    FT_Glyph glyph;
    FT_Get_Glyph(slot,&glyph);
    FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_TRUNCATE, bbox );
    if((bbox->xMax)> temp_bbox.xMax)
        temp_bbox.xMax = bbox->xMax;
    if((bbox->xMin)<temp_bbox.xMin)
        temp_bbox.xMin = bbox->xMin;
    *bbox = temp_bbox;
    return  slot->bitmap;

    // //  free glyph
    // FT_Done_Glyph(slot);
    // slot  =  NULL;
 
    // //  free face
    // FT_Done_Face(g_pFTFace);
    // g_pFTFace  =  NULL;
    
 
    // //  free FreeType Lib
    // FT_Done_FreeType(g_pFTLib);
    // g_pFTLib  =  NULL;

}


