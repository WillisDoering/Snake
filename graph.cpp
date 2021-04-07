/***************************************************************************//**
 * @file 
 * 
 * @brief Functions for the Graph class
 ******************************************************************************/
#include "graph.h"


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Constructor for the Graph class. This will create an empty graph.
 ****************************************************************************/
Graph::Graph() : numVertices(0), numEdges(0) {}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Deconstructor for the Graph class.
 ****************************************************************************/
Graph::~Graph() {}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Constructor for the Graph class. This will create an graph from istream
 * input.
 * 
 * @param[in]	s_in - input from istream
 ****************************************************************************/
Graph::Graph(std::istream & s_in)
{
	int x, y;
	numEdges = 0;

	while(s_in >> x)
	{
		s_in >> y;
		vertices[x].insert(y);
		numEdges++;
	}

	numVertices = vertices.size();
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Constructor for the Graph class. This will create an graph from a 1d array 
 * that represents the playing board.
 * 
 * @param[in]	grid - pointer to 1d array representing playing board
 * @param[in]	width - width of playing board
 * @param[in]	height - height of playing board
 ****************************************************************************/
Graph::Graph(const int *grid, int width, int height)
{
	numVertices = width * height;
	numEdges = 0;
	
	for(int i=0; i < numVertices; i++)
	{
		if(validCell(i))
		{
			//Check top
			if((i-width) >= 0)
				if(validCell(i-width))
				{
					vertices[i].insert(i-width);
					numEdges++;
				}
			//Check left
			if((i%width) > 0)
				if(validCell(i-1))
				{
					vertices[i].insert(i-1);
					numEdges++;
				}
			//Check right
			if((i+1) < numVertices && ((i+1)%width) > 0)
				if(validCell(i+1))
				{
					vertices[i].insert(i+1);
					numEdges++;
				}
			//Check down
			if((i+width) < numVertices && ((i+1)/width) < height)
				if(validCell(i+width))
				{
					vertices[i].insert(i+width);
					numEdges++;
				}
		}
	}
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Adds an edge from vertex x to vertex y
 * 
 * @param[in]	x_in - starting vertex
 * @param[in]	y_in - target vertex
 ****************************************************************************/
void Graph::addEdge(int x_in, int y_in)
{
	vertices[x_in].insert(y_in);
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Retuns the set of vertices adjacent to vertex x_in
 * 
 * @param[in]	x_in - vertex being evaluated
 * 
 * @returns		The set of vertices adjacent to vertex x_in
 ****************************************************************************/
std::set<int> Graph::adj(int x_in) const
{
	return vertices.at(x_in);
}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Gets number of edges in Graph
 * 
 * @returns	numEdges - number of edges in Graph
 ****************************************************************************/
int Graph::E() const {return numEdges;}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Prints Graph with connected vertices
 ****************************************************************************/
void Graph::print()
{
	for(auto i : vertices)
	{
		std::cout << i.first << ": ";
		for(auto j : i.second)
			std::cout << j << " ";
		std::cout << std::endl;
	}
}

/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Gets number of vertices in Graph
 * 
 * @returns	numVertices - number of vertices in Graph
 ****************************************************************************/
int Graph::V() const {return numVertices;}


/*************************************************************************//**
 * @author William Doering
 * 
 * @par Description: 
 * Returns a set of the vertices in the Graph
 * 
 * @returns	V - set of vertices in Graph
 ****************************************************************************/
std::set<int> Graph::Vertices() const
{
	std::set<int> V;
	for(auto i : vertices)
		V.insert(i.first);

	return V;
}
