/***************************************************************************//**
 * @file 
 *
 * @brief Heatmap class. Used to traverse the game field and make a heatmap
 ******************************************************************************/
#ifndef HEATMAP_H
#define HEATMAP_H
#include <queue>
#include "graph.h"
#define SIZE PLAYFIELD_HEIGHT*PLAYFIELD_WIDTH
#define checkHeat(i) (heat[i] < best_adj && heat[i] != -1)

/*! @brief Heatmap of the playing field*/
class Heatmap
{
   int heat[SIZE] = {0};   /*!< Heatmap of board*/
   int head_pos;     /*!< Position of snake head*/

   void generateMap(Graph &map, const int *grid);

public:
   Heatmap(Graph &map, const Playfield *pf);
   ~Heatmap();

   ValidMove moveTowards(const int *grid, int pos);
   int findItem(const int *grid, int item);
   void print();
};

#endif