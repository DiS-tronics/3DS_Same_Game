/*********************************************************************************/
/*!
 * \file      main.c
 *
 * \brief     The Same Game v0.1 --> MAIN File
 *
 * \details   A game where blocks with different colors are ordered
 * \n         randomly to form a field. Blocks which have at least one
 * \n         neighbor with the same color could be deleted. If blocks
 * \n         are deleted the remaining blocks always move up to the 
 * \n         left bottom corner of the game board. The goal of the
 * \n         Same Game is to delete all blocks of the field.
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
int iMode;                             // game mode --> for future use

//*==============================================================================*/
/*  main                                                                         */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     MAIN Function
 *
 * \details   Contains the overall structure of the program.
 *
 * \param     argc, argv
 *
 * \return    error message --> 0 means program exit without an error
 */
/*===============================================================================*/
int main(int argc, char **argv) 
{
	int iRemaining;                      // counting remainig blocks   
	int iEColumn, iERow;                 // game board coordinates
	bool bGameOver = false;              // game over checking

	SAGA_GameInit();                     // create a game field
	
	gfxInitDefault();                    // initialize graphics
	//gfxSet3D(true);                    // using stereoscopic 3D (planed for the future)
	
	// double buffering isn't needed here, thus a image is drawn only once on screen
	gfxSetDoubleBuffering(GFX_TOP, false); 

	
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	// initialize the render target
	C3D_RenderTarget* target = C3D_RenderTargetCreate(240, 320, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetClear(target, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
	C3D_RenderTargetSetOutput(target, GFX_BOTTOM, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

	RDR_SceneInit();                     // initialize the scene
                 
	bool bTouched = false;               // if bottom screen is touched
	bool bEND = false;                   // if game has ended
	 
	touchPosition touch = { 0 };
	touchPosition t_queue = { 0 };

	iMode = NEW_GAME_MODE;

	// Main loop
	while (aptMainLoop()) 
	{
		if(iMode == NEW_GAME_MODE)        // do as long as new game is choosen
		{
			RDR_DrawSplashScreen(GFX_TOP, game_bgr, game_bgr_size, 0);
		
			SAGA_SetupBoard();                 // fill game board with random colors
			RDR_DrawGameBoard();               // draw the board on the screen

			iMode = GAME_PLAY_MODE;            // enter game mode
		}

		if(iMode == GAME_PLAY_MODE)        // do as long as new game is choosen
    {
			if (!bGameOver)                    // do till game is over
			{
				hidTouchRead(&touch);            // read the touch screen coordinates	 

				if (VALID_NEW_TOUCH_POS && bTouched == false)
				{
					iERow = touch.py / 32;         // calculate the selected game board row
					iEColumn = touch.px / 32;      // calculate the selected game board column

					SAGA_DeleteBlocks(iERow, iEColumn);  // delete blocks if possible
					RDR_DrawGameBoard();                 // draw the game board on the display
					bGameOver = SAGA_IsGameOver();       // check whether there are still blocks

					t_queue.px = touch.px;         // save the old touch coordinates in x
					t_queue.py = touch.py;         // save the old touch coordinates in y
					bTouched = true;               // start the delay counter for touch detection
				}

				SYS_TouchDelay(&bTouched);       // non-blocking delay for touch input

				// animated movement of the sprites --> for future use
				//RDR_MoveSprites();
				
				RDR_SceneRender(target);         // Render the game scene
			}
			else
			{
				if (!bEND)                       // do this after game is finished
				{
					// check if there are undeletable blocks remaining
					iRemaining = SAGA_GetRemainingCount(); 
				
					// the game is only won if no blocks are remaining
					if (iRemaining == 0)
						RDR_DrawSplashScreen(GFX_TOP, won_bgr, won_bgr_size, 0);
					else
						RDR_DrawSplashScreen(GFX_TOP, over_bgr, over_bgr_size, 0);
					bEND = true;
				}
			}
		
			RDR_SceneRender(target);         // Render the game scene
			
			if(bEND)
			{
				SYS_WaitForInput(KEY_A);
				bEND = false;
				bGameOver = false;
				iMode = NEW_GAME_MODE;
			}
		}

		if(SYS_UserExit())               // exit the program if START is pressed
			break;

		gfxSwapBuffers();
	}
	

	SAGA_DeleteBoard();

	// Deinitialize the scene
	RDR_SceneExit();

	// Deinitialize graphics
	C3D_Fini();
	gfxExit();
	return 0;
}

/*--------------------------------------END--------------------------------------*/
