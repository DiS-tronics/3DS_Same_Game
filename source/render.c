/*********************************************************************************/
/*!
 * \file      render.c
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

/*-------------------------------------------------------------------------------*/
/*  Include files                                                                */
/*-------------------------------------------------------------------------------*/
#include "system.h"

/*-------------------------------------------------------------------------------*/
/*  Global variables                                                             */
/*-------------------------------------------------------------------------------*/
Sprite sprites[NUM_SPRITES];

/*struct { float left, right, top, bottom; } images[4] = {
	{0.0f, 0.5f, 0.0f, 0.5f},
	{0.5f, 1.0f, 0.0f, 0.5f},
	{0.0f, 0.5f, 0.5f, 1.0f},
	{0.5f, 1.0f, 0.5f, 1.0f},
};*/

// blue, red, yellow, green, grey, purple, orange, black
struct { float left, right, top, bottom, left2, right2, top2, bottom2; } images[8] = {
	{ 0.0f, 0.25f, 0.0f, 0.5f },
	{ 0.25f, 0.5f, 0.0f, 0.5f },
	{ 0.0f, 0.25f, 0.5f, 1.0f },
	{ 0.25f, 0.5f, 0.5f, 1.0f },
	{ 0.5f, 0.75f, 0.0f, 0.5f },
	{ 0.75f, 1.0f, 0.0f, 0.5f },
	{ 0.5f, 0.75f, 0.5f, 1.0f },
	{ 0.75f, 1.0f, 0.5f, 1.0f },
};

static DVLB_s* vshader_dvlb;
static shaderProgram_s program;
static int uLoc_projection;
static C3D_Mtx projection;

static C3D_Tex spritesheet_tex;

//*==============================================================================*/
/*  RDR_DrawSplashScreen                                                         */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Display picture
 *
 * \details   Display specified picture on the top screen, also the left or
 * \n         right buffer of the screen could be selected.
 *
 * \param     image, image size, left or right frame buffer
 *
 * \return    none
 */
/*===============================================================================*/
void RDR_DrawSplashScreen(gfxScreen_t screen, const u8 image[], u32 image_size, u8 leftOrRight)
{            
	// get the top screen's frame buffer
	u8* ft = gfxGetFramebuffer(screen, leftOrRight?GFX_LEFT:GFX_RIGHT, NULL, NULL); 
	
	// copy image in the top screen's frame buffer
	memcpy(ft, image, image_size); 	
	
	// flush and swap framebuffers
	gfxFlushBuffers(); 
	gfxSwapBuffers();
}

//*==============================================================================*/
/*  RDR_DrawGameBoard                                                            */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Define images for sprites
 *
 * \details   Define images for the sprites used to display the game board
 * \n         on the bottom display.
 *
 * \param     none
 *
 * \return    none
 */
/*===============================================================================*/
void RDR_DrawGameBoard(void)
{
	int Color;
	int row, col, index;

	for (row = 0; row < NUMOFROWS; row++)
	{
		for (col = 0; col < NUMOFCOLUMN; col++)
		{
			Color = SAGA_GetBlockColor(row, col);

			index = row * NUMOFCOLUMN + col;

			sprites[index].x = (col * 32) << 8;
			sprites[index].y = (row * 32 + 7) << 8;
			//sprites[index].image = rand() % 7;

			if (Color == RED) {
				sprites[index].image = RED_SPRITE;
			}
			else if (Color == YELLOW) {
				sprites[index].image = YELLOW_SPRITE;
			}
			else if (Color == BLUE) {
				sprites[index].image = BLUE_SPRITE;
			}
			else if (Color == BLACK) {
				sprites[index].image = BLACK_SPRITE;
			}
		}
	}
}


/*-------------------------------------------------------------------------------*/
/*  Rendering functions                                                          */
/*-------------------------------------------------------------------------------*/

//---------------------------------------------------------------------------------
void RDR_DrawSprite( int x, int y, int width, int height, int image ) {
//---------------------------------------------------------------------------------

	float left = images[image].left;
	float right = images[image].right;
	float top = images[image].top;
	float bottom = images[image].bottom;

	// Draw a textured quad directly
	C3D_ImmDrawBegin(GPU_TRIANGLES);
	C3D_ImmSendAttrib(x, y, 0.5f, 0.0f); // v0=position
	C3D_ImmSendAttrib( left, top, 0.0f, 0.0f);

	C3D_ImmSendAttrib(x+width, y+height, 0.5f, 0.0f);
	C3D_ImmSendAttrib( right, bottom, 0.0f, 0.0f);

	C3D_ImmSendAttrib(x+width, y, 0.5f, 0.0f);
	C3D_ImmSendAttrib( right, top, 0.0f, 0.0f);

	C3D_ImmSendAttrib(x, y, 0.5f, 0.0f); // v0=position
	C3D_ImmSendAttrib( left, top, 0.0f, 0.0f);

	C3D_ImmSendAttrib(x, y+height, 0.5f, 0.0f);
	C3D_ImmSendAttrib( left, bottom, 0.0f, 0.0f);

	C3D_ImmSendAttrib(x+width, y+height, 0.5f, 0.0f);
	C3D_ImmSendAttrib( right, bottom, 0.0f, 0.0f);

	C3D_ImmDrawEnd();
}

//---------------------------------------------------------------------------------
void RDR_SceneInit(void) {
//---------------------------------------------------------------------------------

	// Load the vertex shader, create a shader program and bind it
	vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);
	shaderProgramInit(&program);
	shaderProgramSetVsh(&program, &vshader_dvlb->DVLE[0]);
	C3D_BindProgram(&program);

	// Get the location of the uniforms
	uLoc_projection = shaderInstanceGetUniformLocation(program.vertexShader, "projection");

	// Configure attributes for use with the vertex shader
	// Attribute format and element count are ignored in immediate mode
	C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
	AttrInfo_Init(attrInfo);
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0=position
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // v2=texcoord

	// Compute the projection matrix
	// Note: we're setting top to 240 here so origin is at top left.
	Mtx_OrthoTilt(&projection, 0.0, 320.0, 240.0, 0.0, 0.0, 1.0);

	// Configure buffers
	C3D_BufInfo* bufInfo = C3D_GetBufInfo();
	BufInfo_Init(bufInfo);

	unsigned char* image;
	unsigned width, height;

	lodepng_decode32(&image, &width, &height, ballsprites_png, ballsprites_png_size);

	u8 *gpusrc = linearAlloc(width*height*4);

	// GX_DisplayTransfer needs input buffer in linear RAM
	u8* src=image; u8 *dst=gpusrc;

	// lodepng outputs big endian rgba so we need to convert
	for(int i = 0; i<width*height; i++) {
		int r = *src++;
		int g = *src++;
		int b = *src++;
		int a = *src++;

		*dst++ = a;
		*dst++ = b;
		*dst++ = g;
		*dst++ = r;
	}

	// ensure data is in physical ram
	GSPGPU_FlushDataCache(gpusrc, width*height*4);

	// Load the texture and bind it to the first texture unit
	C3D_TexInit(&spritesheet_tex, width, height, GPU_RGBA8);

	// Convert image to 3DS tiled texture format
	GX_DisplayTransfer ((u32*)gpusrc, GX_BUFFER_DIM(width,height), (u32*)spritesheet_tex.data, GX_BUFFER_DIM(width,height), TEXTURE_TRANSFER_FLAGS);
	gspWaitForPPF();

	C3D_TexSetFilter(&spritesheet_tex, GPU_LINEAR, GPU_NEAREST);
	C3D_TexBind(0, &spritesheet_tex);

	free(image);
	linearFree(gpusrc);

	// Configure the first fragment shading substage to just pass through the texture color
	// See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
	C3D_TexEnv* env = C3D_GetTexEnv(0);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, 0, 0);
	C3D_TexEnvOp(env, C3D_Both, 0, 0, 0);
	C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);

	//srand(time(NULL));

	/*for(i = 0; i < NUM_SPRITES; i++) {
		//random place and speed
		sprites[i].x = (rand() % (400 - 32 )) << 8;
		sprites[i].y = (rand() % (240 - 32 )) << 8 ;
		sprites[i].dx = (rand() & 0xFF) + 0x100;
		sprites[i].dy = (rand() & 0xFF) + 0x100;
		sprites[i].image = i;//rand() & 3;

		if(rand() & 1)
			sprites[i].dx = -sprites[i].dx;
		if(rand() & 1)
			sprites[i].dy = -sprites[i].dy;
	}*/
	
	//RDR_DrawGameBoard();

	// Configure depth test to overwrite pixels with the same depth (needed to draw overlapping sprites)
	C3D_DepthTest(true, GPU_GEQUAL, GPU_WRITE_ALL);
}


//---------------------------------------------------------------------------------
void RDR_MoveSprites(void) {
//---------------------------------------------------------------------------------

	int i;

	for(i = 0; i < NUM_SPRITES; i++) {
		sprites[i].x += sprites[i].dx;
		sprites[i].y += sprites[i].dy;
			
		//check for collision with the screen boundaries
		if(sprites[i].x < (1<<8) || sprites[i].x > ((400-32) << 8))
			sprites[i].dx = -sprites[i].dx;

		if(sprites[i].y < (1<<8) || sprites[i].y > ((240-32) << 8))
			sprites[i].dy = -sprites[i].dy;
	}
}

//---------------------------------------------------------------------------------
void RDR_SceneRender(C3D_RenderTarget* target) {
//---------------------------------------------------------------------------------
	int i;
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C3D_FrameDrawOn(target);
	
	// Update the uniforms
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projection);

	for(i = 0; i < NUM_SPRITES; i++) {

		RDR_DrawSprite( sprites[i].x >> 8, sprites[i].y >> 8, 32, 32, sprites[i].image);
	}

	C3D_FrameEnd(0);
}

//---------------------------------------------------------------------------------
void RDR_SceneExit(void) {
//---------------------------------------------------------------------------------

	// Free the shader program
	shaderProgramFree(&program);
	DVLB_Free(vshader_dvlb);
}

/*------------------------------------END----------------------------------------*/