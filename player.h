/***************************************************************************//**
 * @file 
 *
 * @brief Player class. Used in making moves for the snake
 ******************************************************************************/
#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include "graph.h"
#include "heatmap.h"

/*! @brief Player class. Used in making moves for the snake*/
class Player
{
public:
   Player () {}
   ValidMove makeMove(const Playfield *);
private:
   bool obstacleCheck(const int *grid);
   ValidMove normPass(const Playfield *pf);
   ValidMove noObstacles(const int *grid);
   ValidMove evenHeight(const int *grid, int pos);
   ValidMove oddHeight(const int *grid, int pos);
};

#endif
