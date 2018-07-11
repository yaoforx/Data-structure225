/* Your code here! */
/**
 * @file maze.h
 */

#ifndef _MAZE_H_
#define _MAZE_H_

#include <cstdlib>

#include <vector>
#include <queue>
#include <time.h>       /* time */
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
using namespace std;
using namespace cs225;

class SquareMaze
{
	public:
		//No-parameter constructor. 
		SquareMaze();

		//Makes a new SquareMaze of the given height and width.
		void makeMaze (int width, int height);

		//This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y). 
		bool canTravel (int x, int y, int dir) const;
 
		//Sets whether or not the specified wall exists. 
		void setWall (int x, int y, int dir, bool exists);

		//Solves this SquareMaze.
		vector<int> solveMaze ();

		//Draws the maze without the solution.
		PNG * drawMaze () const;

		//This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit. 
		PNG * drawMazeWithSolution ();
        pair<int,int> coor(int x, int y) const;
        PNG * drawCreativeMaze();
    PNG * drawMazeWithSolutionCreative ();

	private:
		//variables
		vector<vector<vector<bool>>> walls_;
		int width_;
		int height_;
		//Helper functions
		//check whether the coordinate is valid
		bool isvalid (int x, int y) const ;
		int unroll(int x, int y) const ;
		pair<int,int> roll(int position) const ;
		vector<int> findShortestPath() ;
		vector<int> getAdjacent(int vertex) ;
		int findmaxpath(vector<int>& distance_map) ;
		int getdirection(int parent, int vertex) ;

};

#endif