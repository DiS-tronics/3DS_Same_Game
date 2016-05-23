/*********************************************************************************/
/*!
 * \file      render.h
 *
 * \brief     The Same Game v0.1 --> GRAPHICS File
 *
 * \details   Graphic and rendering functions used by the project.
 *
 * \note      Hardware:    Nintendo 3DS
 * \n         IDE:         DevkitPro 1.6.0
 * \n         Licence:     GNU General Public License V3
 * \n
 * \warning   Copyright:   (C) by DiS-tronics Austria               
 *
 * \author 	  DiS-tronics
 * \date      May 2016
 */
/*********************************************************************************/
#ifndef RENDER_H
#define RENDER_H

/*-------------------------------------------------------------------------------*/
/*  Defines                                                                      */
/*-------------------------------------------------------------------------------*/
#define CLEAR_COLOR 0x000000FF

// Used to transfer the final rendered display to the framebuffer
#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

// Used to convert textures to 3DS tiled format
// Note: vertical flip flag set so 0,0 is top left of texture
#define TEXTURE_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(1) | GX_TRANSFER_OUT_TILED(1) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGBA8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

#define NUM_SPRITES     70
#define BLUE_SPRITE     0
#define RED_SPRITE      1
#define YELLOW_SPRITE   2
#define BLACK_SPRITE    7


/*-------------------------------------------------------------------------------*/
/*  Type definitions                                                             */
/*-------------------------------------------------------------------------------*/
typedef struct {  // simple sprite struct
	int x,y;			  // screen co-ordinates 
	int dx, dy;			// velocity
	int image;
}Sprite;


/*-------------------------------------------------------------------------------*/
/*  Function prototypes                                                          */
/*-------------------------------------------------------------------------------*/
void RDR_DrawSprite( int x, int y, int width, int height, int image );
void RDR_SceneInit(void);
void RDR_MoveSprites(void);
void RDR_SceneRender(C3D_RenderTarget* target);
void RDR_SceneExit(void);
void RDR_DrawGameBoard(void);
void RDR_DrawSplashScreen(gfxScreen_t screen, const u8 image[], u32 image_size, u8 leftOrRight);

//---------------------------------------------------------------------------------
#endif // RENDER_H