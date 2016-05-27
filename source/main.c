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
	RDR_DisplayInit();                   // display and rendering settings
	RDR_SceneInit();                     // initialize the scene
                 
	bool bTouched = false;               // if bottom screen is touched
	touchPosition touch = { 0 };         // save the touch inputs
	touchPosition t_queue = { 0 };       // save old touch inputs for camparison

	iMode = MAIN_MENU_MODE;              // start with the main menu

	
	while (aptMainLoop())                // Main loop
	{
		hidScanInput();                    // check wheter there are user inputs

		if(iMode == MAIN_MENU_MODE)
		{
			RDR_DrawSplashScreen(GFX_TOP, game_bgr, game_bgr_size, 0);
			RDR_DrawSplashScreen(GFX_BOTTOM, menu_bgr, menu_bgr_size, 0);

			u32 kDown = hidKeysDown();
			if(kDown & KEY_A)                      // start new game if button A
			{                                      // is pressed
				iMode = NEW_GAME_MODE;
			}
		}
		
		if(iMode == NEW_GAME_MODE)         // do as long as new game is choosen
		{
			RDR_DrawSplashScreen(GFX_TOP, game_bgr, game_bgr_size, 0);
		
			SAGA_SetupBoard();               // fill game board with random colors
			RDR_DrawGameBoard();             // draw the board on the screen

			iMode = GAME_PLAY_MODE;          // enter game mode
		}

		if(iMode == GAME_PLAY_MODE)        // do as long as new game is choosen
    {
			if (!bGameOver)                  // do till game is over
			{
				hidTouchRead(&touch);          // read the touch screen coordinates	 

				if (VALID_NEW_TOUCH_POS && bTouched == false)
				{
					iERow = touch.py / 32;       // calculate the selected game board row
					iEColumn = touch.px / 32;    // calculate the selected game board column

					SAGA_DeleteBlocks(iERow, iEColumn);  // delete blocks if possible
					RDR_DrawGameBoard();                 // draw the game board on the display
					bGameOver = SAGA_IsGameOver();       // check whether there are still blocks

					t_queue.px = touch.px;       // save the old touch coordinates in x
					t_queue.py = touch.py;       // save the old touch coordinates in y
					bTouched = true;             // start the delay counter for touch detection
				}

				SYS_TouchDelay(&bTouched);     // non-blocking delay for touch input

				// animated movement of the sprites --> for future use
				//RDR_MoveSprites();
				
				RDR_SceneRender();             // Render the game scene
			}
			else                             // do this after game is finished
			{
					// check if there are undeletable blocks remaining
					iRemaining = SAGA_GetRemainingCount(); 
				
					// the game is only won if no blocks are remaining
					if (iRemaining == 0)
						RDR_DrawSplashScreen(GFX_TOP, won_bgr, won_bgr_size, 0);
					else
						RDR_DrawSplashScreen(GFX_TOP, over_bgr, over_bgr_size, 0);
					
					iMode = GAME_END_MODE;       // change to game end mode
			}
		
			RDR_SceneRender();               // Render the game scene
		}
		
		if(iMode == GAME_END_MODE)
		{
			RDR_DrawSplashScreen(GFX_BOTTOM, again_bgr, again_bgr_size, 0);

			u32 kDown = hidKeysDown();
			if(kDown & KEY_A || kDown & KEY_TOUCH) // start new game if button A
			{                                      // or touch screen is pressed
				bGameOver = false;
				iMode = NEW_GAME_MODE;
			}
		}
			

		if(SYS_UserExit())                 // exit the program if START is pressed
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
