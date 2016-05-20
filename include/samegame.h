/*********************************************************************************/
/*!
 * \file      samegame.h
 *
 * \brief     The Same Game v0.1 --> GAME File
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
#ifndef _SAMEGAME_H
#define _SAMEGAME_H

/*-------------------------------------------------------------------------------*/
/*  Defines                                                                      */
/*-------------------------------------------------------------------------------*/
#define BLACK   '*' 		
#define RED     'R' 		
#define YELLOW  'Y' 		
#define BLUE    'B' 		
#define GREEN   'G' 		
#define GRAY    'T' 		
#define PURPLE  'P' 		
#define ORANGE  'O' 		

#define NUMOFCOLUMN  10
#define NUMOFROWS     7
#define BLOCKHEIGHT  32
#define BLOCKWIDTH   32
#define NUMOFCOLORS   3

#define false   0
#define true    1
//#define RAND_MAX  10

// direction enumeration for deleting blocks
enum Direction
{
  DIRECTION_UP,
  DIRECTION_DOWN,
  DIRECTION_LEFT,
  DIRECTION_RIGHT
};

/*-------------------------------------------------------------------------------*/
/*  Function prototypes                                                          */
/*-------------------------------------------------------------------------------*/
void SAGA_GameInit(void);
void SAGA_SetupBoard(void);
char SAGA_GetBlockColor(int row, int col);
int  SAGA_GetColumns(void);
int  SAGA_GetRows(void);
bool SAGA_IsGameOver(void);
int  SAGA_GetRemainingCount(void);
int  SAGA_DeleteBlocks(int row, int col);
int  SAGA_GetNumColors(void);
void SAGA_CreateBoard(void);
void SAGA_DeleteBoard(void);
int  SAGA_DeleteNeighborBlocks(int row, int col, int color, enum Direction direction);
void SAGA_CompactBoard(void);

#endif	/* _SAMEGAME_H */