/*********************************************************************************/
/*!
 * \file      system.c
 *
 * \brief     The Same Game v0.1 --> SYSTEM File
 *
 * \details   General fuctions and defines for the whole project.
 *
 * \note      Hardware:    Nintendo 3DS
 * \n         IDE:         DevkitPro 1.6.0
 * \n		      Licence:     GNU General Public License V3
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

//*==============================================================================*/
/*  SYS_TouchDelay                                                               */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Delay for touch input
 *
 * \details   Non-blocking delay for the touch inputs to provide an intuitive 
 * \n         user experience.
 *
 * \param     *bTouched --> pointer to variable for saving the touch status
 *
 * \return    none
 */
/*===============================================================================*/
void SYS_TouchDelay(bool *bTouched)
{
	static int iCounter = 0;             // static delay counter
	
	if (*bTouched) {                      
		iCounter++;
	}

	if (iCounter > 10) {
		*bTouched = 0;
		iCounter = 0;
	}
}

//*==============================================================================*/
/*  SYS_WaitForInput                                                             */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Delay
 *
 * \details   Blocking delay for special situations.
 *
 * \param     iKey --> specifies the key to wait for
 *
 * \return    none
 */
/*===============================================================================*/
void SYS_WaitForInput(u32 iKey)
{
	gfxSetDoubleBuffering(GFX_BOTTOM, false); 

	while(!(hidKeysDown() & iKey))
	{
		RDR_DrawSplashScreen(GFX_BOTTOM, again_bgr, again_bgr_size, 0);
		hidScanInput();
		gfxSwapBuffers();
	}
}

//*==============================================================================*/
/*  SYS_UserExit                                                                 */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     User wants to exit the program?
 *
 * \details   Check if the user wants to exit  the program by pressing the
 * \n         START button.
 *
 * \param     none
 *
 * \return    true or false
 */
/*===============================================================================*/
bool SYS_UserExit(void)
{
	// Respond to user input
	u32 kDown = hidKeysDown();
	if (kDown & KEY_START)             // if START is pressed
		return 1;                        // break in order to return to hbmenu
	else
		return 0;
}

/*------------------------------------END----------------------------------------*/