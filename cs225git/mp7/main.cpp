#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
    maze.makeMaze(50, 50);
    PNG * actualOutput = maze.drawCreativeMaze() ;
    actualOutput->writeToFile("creative" + string(".png"));
    PNG * actualOutput1= maze.drawMazeWithSolutionCreative() ;
    actualOutput1->writeToFile("creative_soln" + string(".png"));

    return 0;
}
