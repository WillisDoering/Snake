/*****************************************************************************
 * Project Nydus
 ****************************************************************************/
#include "player.h"

/*************************************************************************//**
 * @file 
 *
 * @Main file for player Nydus
 ****************************************************************************/


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * This function will make a decision for what directon to move.
 * 
 * @param[in]  pf - Playfield class being used by the game
 *
 * @returns    move - move chosen for player
 ****************************************************************************/
ValidMove Player::makeMove(const Playfield *pf)
{
   const int *grid = pf->getGrid();
   
   //Check for obstacles and run corresponding function.
   static bool hasObstacles = obstacleCheck(grid);

   if(!hasObstacles)
      return noObstacles(grid);
   
   return normPass(pf);
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * This function will check for obstacles in the playfield.
 * 
 * @param[in]  grid - map of the playfield
 *
 * @returns    true - has obstacles
 * @returns    false - doesn't have obstacles
 ****************************************************************************/
bool Player::obstacleCheck(const int *grid)
{
   for(int i=0; i < SIZE; i++)
   {
      switch(grid[i])
      {
      case CLEAR_VALUE:
      case HEAD_VALUE:
      case FOOD_VALUE:
         break;
      case TAIL_VALUE:
         return true;
      }
   }
   return false;
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * This function controls snake movement if there are obstacles. It uses a
 * general sweep motion across the board to prevent colisions.
 * 
 * @param[in]  pf - Playfield class for the snake
 *
 * @returns    move - best move for the snake
 ****************************************************************************/
ValidMove Player::normPass(const Playfield *pf)
{
   const int *grid = pf->getGrid();
   static ValidMove move;
   ValidMove nextMove;
   int food;
   
   Graph map(grid, PLAYFIELD_WIDTH, PLAYFIELD_HEIGHT);
   
   Heatmap path(map, pf);
   food = path.findItem(grid, FOOD_VALUE);

   nextMove = path.moveTowards(grid, food);

   if(nextMove != NONE)
      move = nextMove;

   return move;
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * This function controls snake movement if there are no obstacles. There are
 * two separate algorithms, one for an odd height and one for an even one.
 * 
 * @param[in]  grid - map of the playfield
 *
 * @returns    ValidMove - Move selected for snake
 ****************************************************************************/
ValidMove Player::noObstacles(const int *grid)
{ 
   int pos;
   ValidMove move;

   //Find Head
   for(int i=0; i<SIZE; i++)
      if(grid[i] == HEAD_VALUE)
         pos = i;

   //Get next move based on even or odd
   if(PLAYFIELD_HEIGHT%2)
      move = oddHeight(grid, pos);
   else
      move = evenHeight(grid, pos);

   //Check move
   for(int i=0; i<SIZE; i++)
      if(grid[i] == CLEAR_VALUE)
         return move;

   return NONE;
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * This function selects a move for a playfield without obstacles that has an
 * even height
 * 
 * @param[in]  grid - map of the playfield
 * @param[in]  pos - position of snake head
 *
 * @returns    ValidMove - Move selected for snake
 ****************************************************************************/
ValidMove Player::evenHeight(const int *grid, int pos)
{
   //If at origin
   if(pos == 0)
      return RIGHT;

   //If along left side, but not origin
   if(pos%PLAYFIELD_WIDTH == 0)
      return DOWN;

   //If on top row and not above cases
   if((pos/PLAYFIELD_WIDTH) == (PLAYFIELD_HEIGHT-1))
      return LEFT;

   //Even or odd row check
   if((pos/PLAYFIELD_WIDTH)%2 == 0)
   {
      if((pos%PLAYFIELD_WIDTH) == (PLAYFIELD_WIDTH-1))
         return UP;
      else
         return RIGHT;
   }
   else
   {
            if((pos%PLAYFIELD_WIDTH) == 1)
         return UP;
      else
         return LEFT;
   }

   //Return if no cases are found (an error)
   return NONE;
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * This function selects a move for a playfield without obstacles that has an
 * odd height
 * 
 * @param[in]  grid - map of the playfield
 * @param[in]  pos - position of  snake head
 *
 * @returns    ValidMove - Move selected for snake
 ****************************************************************************/
ValidMove Player::oddHeight(const int *grid, int pos)
{
   static bool skip = false;
   int height = PLAYFIELD_HEIGHT - 1;

   //If at origin
   if(pos == 0)
   {
      skip = !skip;
      return RIGHT;
   }

   //If along left side, but not origin
   if(pos%PLAYFIELD_WIDTH == 0)
      return DOWN;

   //If on top row and not above cases
   if((pos/PLAYFIELD_WIDTH) == (height))
      return LEFT;

   //If on second to top row and not above cases
   if((pos/PLAYFIELD_WIDTH) == (height-1))
   {
      if(skip && ((pos%PLAYFIELD_WIDTH) == (PLAYFIELD_WIDTH-1)))
         return UP;
      return LEFT;
   }

   //Even or odd row check
   if((pos/PLAYFIELD_WIDTH)%2 == 0)
   {
      if((pos%PLAYFIELD_WIDTH) == (PLAYFIELD_WIDTH-1))
         return UP;
      else
         return RIGHT;
   }
   else
   {
            if((pos%PLAYFIELD_WIDTH) == 1)
         return UP;
      else
         return LEFT;
   }

   //Return if no cases are found (an error)
   return NONE;

}