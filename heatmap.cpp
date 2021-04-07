/***************************************************************************//**
 * @file 
 *
 * @brief Contains functions for the Heatmap class
 ******************************************************************************/
#include "heatmap.h"
#include <iomanip>


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Generates the heatmap
 * 
 * @param[in]  map - adjacency map of the game board
 * @param[in]  grid - map of game board
 ****************************************************************************/
void Heatmap::generateMap(Graph &map, const int *grid)
{
   //Queue setup
   std::queue<int> curr;
   curr.push(head_pos);
   bool visited[SIZE] = {false};
   std::set<int> adj_set;
   int curr_heat = 0;
   heat[head_pos] = 0;
   visited[head_pos] = true;

   while(!curr.empty())
   {
      adj_set = map.adj(curr.front());
      curr_heat = heat[curr.front()];
      curr.pop();

      for(auto i : adj_set)
         if(!visited[i])
         {
            heat[i] = curr_heat + 1;
            curr.push(i);
            visited[i] = true;
         }
   }

   for(int i=0; i<SIZE; i++)
      if(visited[i] == false)
         heat[i] = -1;
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Constructor for the Heatmap class
 * 
 * @param[in]  map - adjacency map of the game board
 * @param[in]  pf - Playfield class for snake
 ****************************************************************************/
Heatmap::Heatmap(Graph &map, const Playfield *pf)
{
   std::set<int> adj;

   const int *grid = pf->getGrid();
   head_pos = findItem(grid, HEAD_VALUE);
   generateMap(map, grid);
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Deconstructor for the Heatmap class
 ****************************************************************************/
Heatmap::~Heatmap() {}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Finds the best move to get to the target.
 * 
 * @param[in]  grid - Map of playing field
 * @param[in]  pos - target destination
 * 
 * @returns    move - current best move to get to target location
 * @returns    NONE - no path was found
 ****************************************************************************/
ValidMove Heatmap::moveTowards(const int *grid, int pos)
{
   int best_adj = -1;
   int new_pos;

   //If target is adjacent to head
   if(heat[pos] == 1)
   {
      if(head_pos <= (pos-PLAYFIELD_WIDTH))
         return UP;
      if(head_pos == (pos-1))
         return RIGHT;
      if(head_pos == (pos+1))
         return LEFT;
      if(head_pos >= (pos+PLAYFIELD_WIDTH))
         return DOWN;
      return NONE;
   }

   //Recurse until target is adjacent to head
   //Check bottom
   if((pos-PLAYFIELD_WIDTH) >= 0 && heat[pos-PLAYFIELD_WIDTH] != -1)
   {
      best_adj = heat[pos-PLAYFIELD_WIDTH];
      new_pos = pos-PLAYFIELD_WIDTH;
   }
   //Check left
   if((pos%PLAYFIELD_WIDTH) > 0)
      if(checkHeat(pos-1) || best_adj == -1)
      {
         best_adj = heat[pos-1];
         new_pos = pos-1;
      }
   //Check right
   if((pos+1) < SIZE && ((pos+1)%PLAYFIELD_WIDTH) > 0)
      if(checkHeat(pos+1) || best_adj == -1)
      {
         best_adj = heat[pos+1];
         new_pos = pos+1;
      }
   //Check top
   if(((pos/PLAYFIELD_WIDTH)+1) < PLAYFIELD_HEIGHT)
      if(checkHeat(pos+PLAYFIELD_WIDTH) || best_adj == -1)
      {
         best_adj = heat[pos+PLAYFIELD_WIDTH];
         new_pos = pos+PLAYFIELD_WIDTH;
      }
   //No path
   if(best_adj == -1)
      return NONE;

   //Recurse and return result
   return moveTowards(grid, new_pos);
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Finds an item in the playfield
 * 
 * @param[in]  grid - map of game board
 * @param[in]  item - item searched for
 *
 * @returns    food - location of item in array
 * @returns    -1 - item not found
 ****************************************************************************/
int Heatmap::findItem(const int *grid, int item)
{
   for(int i=0; i<SIZE; i++)
      if(grid[i] == item)
         return i;
   
   return -1;
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Prints out heatmap
 ****************************************************************************/
void Heatmap::print()
{
   for(int row=PLAYFIELD_HEIGHT-1; row>=0; row--)
   {
      for(int col=0; col<PLAYFIELD_WIDTH; col++)
      {
         std::cout << std::setw(3) << heat[row*PLAYFIELD_WIDTH+col] << ' ';
      }
      std::cout << std::endl;
   }
}
