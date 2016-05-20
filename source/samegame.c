/*********************************************************************************/
/*!
 * \file      samegame.c
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

/*-------------------------------------------------------------------------------*/
/*  Include files                                                                */
/*-------------------------------------------------------------------------------*/
#include "system.h"
#include "samegame.h"
#include "stdlib.h"
#include <malloc.h>

/*-------------------------------------------------------------------------------*/
/*  Global variables                                                             */
/*-------------------------------------------------------------------------------*/
int** m_arrBoard;                      // pointer for the game data
static char m_arrColors[8];            // list of colors
int m_nColumns;                        // board size information
int m_nRows;                           // board size information
int m_nRemaining;                      // number of remaining blocks
int m_nColors;                         // number of colors

//*==============================================================================*/
/*  SAGA_GameInit                                                                */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Initialize the game
 *
 * \details   Initialize the game, allocate the memory for the board and 
 * \n         fill it up with random colors.
 *
 * \param     none
 *
 * \return    none
 */
/*===============================================================================*/
void SAGA_GameInit(void)
{
  m_arrBoard = NULL;
  m_nColumns = NUMOFCOLUMN;
  m_nRows = NUMOFROWS;
  m_nRemaining = 0; 
  m_nColors = NUMOFCOLORS;
  
  m_arrColors[0] = BLACK;
  m_arrColors[1] = RED;
  m_arrColors[2] = YELLOW;
  m_arrColors[3] = BLUE;
  m_arrColors[4] = GREEN;
  m_arrColors[5] = GRAY;
  m_arrColors[6] = PURPLE;
  m_arrColors[7] = ORANGE;
  
  srand(time(NULL));
  
  SAGA_SetupBoard();
}

//*==============================================================================*/
/*  SAGA_SetupBoard                                                              */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Randomly setup the board
 *
 * \details   Allocate memory for the board and fill it up with random colors. 
 *
 * \param     none
 *
 * \return    none
 */
/*===============================================================================*/
void SAGA_SetupBoard(void)
{
  int row, col;
  //  Create the board if needed
  if(m_arrBoard == NULL)
    SAGA_CreateBoard();
  
  //  Randomly set each square to a color
  for(row = 0; row < m_nRows; row++)
    for(col = 0; col < m_nColumns; col++)
    {
      m_arrBoard[row][col] = (rand() % m_nColors) + 1;
    }
  
  //  Set the number of spaces remaining
  m_nRemaining = m_nRows * m_nColumns;
}

//*==============================================================================*/
/*  SAGA_GetBlockColor                                                           */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Get the color of specific block
 *
 * \details   Returns the color of a specified block of the board, needed for 
 * \n         displaying the board on the screen.
 *
 * \param     row, column
 *
 * \return    none
 */
/*===============================================================================*/
char SAGA_GetBlockColor(int row, int col)
{
  //  Check the bounds of the array
  if(row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
    return m_arrColors[0];
  return m_arrColors[m_arrBoard[row][col]];
}

//*==============================================================================*/
/*  SAGA_DeleteBoard                                                             */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Delete the gameboard
 *
 * \details   Delete the gameboard and free the memory. 
 *
 * \param     none
 *
 * \return    none
 */
/*===============================================================================*/
void SAGA_DeleteBoard(void)
{
  int row;
  
  //  Delete each colomn
  for(row = 0; row < m_nRows; row++)
  {
    free(m_arrBoard[row]);
  }
  
  // Finally delete the array of rows
  free(m_arrBoard);
}

//*==============================================================================*/
/*  SAGA_CreateBoard                                                             */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Create a new gameboard
 *
 * \details   Allocate memory and create the 2-dimensional gameboard array. 
 *
 * \param     none
 *
 * \return    none
 */
/*===============================================================================*/
void SAGA_CreateBoard(void)
{
  int row, col;
  
  //  Create the array of rows
  m_arrBoard = (int**) malloc(m_nRows * sizeof(int*));
  if(!m_arrBoard) 
		printf("\x1b[10;13HThe Same Game");
  
	//  Create each row
  for(row = 0; row < m_nRows; row++)
  {
    m_arrBoard[row] = (int*) malloc(m_nColumns * sizeof(int*));
	
	//  Set each square to be empty
	for(col = 0; col < m_nColumns; col++)
    {
      m_arrBoard[row][col] = 0;
    }
  }
}

//*==============================================================================*/
/*  SAGA_GetColumns                                                              */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Get number of columns
 *
 * \details   Part of accessor functions to get board size information --> 
 * \n         return the number of columns of the gameboard. 
 *
 * \param     none
 *
 * \return    m_nColumns --> number of columns
 */
/*===============================================================================*/
int SAGA_GetColumns(void) 
{ 
  return m_nColumns; 
}

//*==============================================================================*/
/*  SAGA_GetRows                                                                 */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Get number of rows
 *
 * \details   Part of accessor functions to get board size information --> 
 * \n         return the number of rows of the gameboard.
 *
 * \param     none
 *
 * \return    m_nRows --> number of rows
 */
/*===============================================================================*/
int SAGA_GetRows(void) 
{ 
  return m_nRows; 
}

//*==============================================================================*/
/*  SAGA_GetRemainingCount                                                       */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Get number of remaining blocks
 *
 * \details   Return the number of the ramaining blocks, especially for deciding
 * \n         wheter the game is won after there are no deletable blocks remaining. 
 *
 * \param     none
 *
 * \return    m_nRemaining --> number of remaining blocks
 */
/*===============================================================================*/
int SAGA_GetRemainingCount(void)
{
  return m_nRemaining; 
}

//*==============================================================================*/
/*  SAGA_GetNumColors                                                            */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Get number of used colors
 *
 * \details   Return the number of used colors defined for the game. 
 *
 * \param     none
 *
 * \return    m_nColors --> number of colors
 */
/*===============================================================================*/
int SAGA_GetNumColors(void) 
{
  return m_nColors; 
}

//*==============================================================================*/
/*  SAGA_IsGameOver                                                              */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Is the game over?
 *
 * \details   Check if there are still touching blocks with the same color. 
 *
 * \param     none
 *
 * \return    true or false
 */
/*===============================================================================*/
bool SAGA_IsGameOver(void)
{
  int col, row, nColor;
  
	//  Go column by column, left to right
  for(col = 0; col < m_nColumns; col++)
  {
    //  Row by row, bottom to top
    for(row = m_nRows - 1; row >= 0; row--)
    {
      nColor = m_arrBoard[row][col];
      //  Once we hit background, this column is done
      if(nColor == 0)
        break;
      else
      {
        //  Check above and right
        if(row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor)
          return false;
        else if(col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor)
          return false;
      }
    }
  }
  
	//  No two adjacent block found
  return true;
}

//*==============================================================================*/
/*  SAGA_DeleteBlocks                                                            */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Delete blocks if possible
 *
 * \details   Function to delete all adjacent blocks with the same color. 
 *
 * \param     row, column
 *
 * \return    nCount --> number of deleted pieces
 */
/*===============================================================================*/
int SAGA_DeleteBlocks(int row, int col)
{
  //  Make sure that the row and column are valid
  if(row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
    return -1;
  
  int nColor = m_arrBoard[row][col];

	//  Can't delete background blocks
  if(nColor == 0)
    return -1;
  
	//	First check if there are any of the adjacent sides with the same color 
  int nCount = -1;
  if((row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor) ||
     (row + 1 < m_nRows && m_arrBoard[row + 1][col] == nColor) ||
     (col - 1 >= 0 && m_arrBoard[row][col - 1] == nColor) ||
     (col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor))
  {
    //	Then call the recursive function to eliminate all
    //  other touching blocks with same color
    m_arrBoard[row][col] = 0;
    nCount = 1;
    //	Recursive call for up
    nCount += SAGA_DeleteNeighborBlocks(row - 1, col, nColor, DIRECTION_DOWN);
    //	Recursive call for down
    nCount += SAGA_DeleteNeighborBlocks(row + 1,col, nColor, DIRECTION_UP);
    //	Recursive call for left
    nCount += SAGA_DeleteNeighborBlocks(row, col - 1, nColor, DIRECTION_RIGHT);
    //	Recursive call for right
    nCount += SAGA_DeleteNeighborBlocks(row, col + 1, nColor, DIRECTION_LEFT);
    //	Finally compact the board
    SAGA_CompactBoard();
    //  Remove the count from the number remaining
    m_nRemaining -= nCount;
  }
  //  Return the total number of pieces deleted
  return nCount;
}

//*==============================================================================*/
/*  SAGA_DeleteNeighborBlocks                                                    */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Rekursivly deleting blocks
 *
 * \details   Rekursive helpfunction for deleting adjacent blocks with same color. 
 *
 * \param     row, column, direction to look for
 *
 * \return    nCount --> number of deleted pieces
 */
/*===============================================================================*/
int SAGA_DeleteNeighborBlocks(int row, int col, int color, enum Direction direction)
{
  //  Check if it is on the board
  if(row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
    return 0;
  
	//  Check if it has the same color
  if(m_arrBoard[row][col] != color)
    return 0;
  
	int nCount = 1;
  m_arrBoard[row][col] = 0;
  //  If we weren't told to not go back up, check up
  if(direction != DIRECTION_UP)
    nCount += SAGA_DeleteNeighborBlocks(row - 1, col, color, DIRECTION_DOWN);
  //  If we weren't told to not go back down, check down
  if(direction != DIRECTION_DOWN)
    nCount += SAGA_DeleteNeighborBlocks(row + 1, col, color, DIRECTION_UP);
  //  If we weren't told to not go back left, check left
  if(direction != DIRECTION_LEFT)
    nCount += SAGA_DeleteNeighborBlocks(row, col - 1, color, DIRECTION_RIGHT);
  //  If we weren't told to not go back right, check right
  if(direction != DIRECTION_RIGHT)
    nCount += SAGA_DeleteNeighborBlocks(row, col + 1, color, DIRECTION_LEFT);
  
	//  Return the total number of pieces deleted
  return nCount;
}

//*==============================================================================*/
/*  SAGA_CompactBoard                                                            */
/*-------------------------------------------------------------------------------*/
/*!
 * \brief     Compact the gmeboard
 *
 * \details   Function to compact the board after blocks are eliminated. 
 *
 * \param     none
 *
 * \return    none
 */
/*===============================================================================*/
void SAGA_CompactBoard(void)
{
  //  First move everything down
  for(int col = 0; col < m_nColumns; col++)
  {
    int nNextEmptyRow = m_nRows - 1;
    int nNextOccupiedRow = nNextEmptyRow;
    while(nNextOccupiedRow >= 0 && nNextEmptyRow >= 0)
    {
      //  First find the next empty row
      while(nNextEmptyRow >= 0 && m_arrBoard[nNextEmptyRow][col] != 0)
        nNextEmptyRow--;
      if(nNextEmptyRow >= 0)
      {
        //  Then find the next occupied row from the next empty row
        nNextOccupiedRow = nNextEmptyRow - 1;
        while(nNextOccupiedRow >= 0 && m_arrBoard[nNextOccupiedRow][col] == 0)
          nNextOccupiedRow--;
        if(nNextOccupiedRow >= 0)
        {
          //  Now move the block from occupied to empty
          m_arrBoard[nNextEmptyRow][col] = m_arrBoard[nNextOccupiedRow][col];
          m_arrBoard[nNextOccupiedRow][col] = 0;
        }
      }
    }
  }
  //  Then move everything from right to left
  int nNextEmptyCol = 0;
  int nNextOccupiedCol = nNextEmptyCol;
  while(nNextEmptyCol < m_nColumns && nNextOccupiedCol < m_nColumns)
  {
    //  First find the next empty column
    while(nNextEmptyCol < m_nColumns && m_arrBoard[m_nRows - 1][nNextEmptyCol] != 0)
      nNextEmptyCol++;
    if(nNextEmptyCol < m_nColumns)
    {
      //  Then find the next column with something in it
      nNextOccupiedCol = nNextEmptyCol + 1;
      while(nNextOccupiedCol < m_nColumns && m_arrBoard[m_nRows - 1][nNextOccupiedCol] == 0)
        nNextOccupiedCol++;
      if(nNextOccupiedCol < m_nColumns)
      {
        //  Move entire column to the left
        for(int row = 0; row < m_nRows; row++)
        {
          m_arrBoard[row][nNextEmptyCol] = m_arrBoard[row][nNextOccupiedCol];
          m_arrBoard[row][nNextOccupiedCol] = 0;
        }
      }
    }
  }
}

//----------------------------------- END --------------------------------------


