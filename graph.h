/***************************************************************************//**
 * @file 
 *
 * @brief Graph class
 ******************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "playfield.h"
#define validCell(i) (grid[i] == CLEAR_VALUE || grid[i] == FOOD_VALUE \
   || grid[i] == HEAD_VALUE)


typedef std::map<int, std::set<int>> map_t;	/*!< specific map used in graph */

/*! @brief Graph of playing board*/
class Graph
{
   map_t vertices;	/*!< map of vertices on the board */
   int numVertices;	/*!< number of verices on the board */
   int numEdges;		/*!< number of edges between vertices on the map */

public:
	Graph();
	~Graph();
	Graph(std::istream & s_in);
	Graph(const int *grid, int width, int height);

   virtual void addEdge(int x_in, int y_in);
   std::set<int> adj(int x_in) const; 
   int E() const; 
   void print();
   int V() const;
	std::set<int> Vertices() const;
};

#endif