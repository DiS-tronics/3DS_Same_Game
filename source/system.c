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

/*------------------------------------END----------------------------------------*/