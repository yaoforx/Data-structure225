
#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance)
:start_(start),png_(png),tolerance_(tolerance)
 {  
  /** @todo [Part 1] */
 
  stack.push(start);
  startX = start.x;
  startY = start.y;
  unsigned int row = png.height();
  unsigned int col = png.width();
  visited.resize(col,vector<bool>(row));
  for(unsigned int i = 0; i < col; i++)
    for(unsigned int j = 0; j < row; j++){
      visited[i][j] = false;
    }
    //visited[startX][startY] = true;
}



/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS * dfs = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*dfs,start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  unsigned int x = point.x;
  unsigned int y = point.y;
  HSLAPixel & startPixel = png_.getPixel(startX,startY);
  if (x + 1 < png_.width() && !visited[x+1][y]) 
    { 
      HSLAPixel & right = png_.getPixel(x + 1,y);
      if(calculateDelta(right,startPixel) <=tolerance_){ 
        stack.push(Point(x+1,y));
      }
    }
  if (y + 1 < png_.height() && !visited[x][y+1]) {
        HSLAPixel & left = png_.getPixel(x,y + 1);
      if(calculateDelta(left,startPixel) <=tolerance_){ 
        stack.push(Point(x,y + 1));
      }
  }
  if ((int)x - 1 >= 0 &&  !visited[x - 1][y]) {
       HSLAPixel & below = png_.getPixel(x -1,y);
      if(calculateDelta(below,startPixel) <=tolerance_){ 
        stack.push(Point(x-1,y));
      }
  }
  if ((int)y - 1 >= 0 &&  !visited[x][y - 1]) {
       HSLAPixel & above = png_.getPixel(x,y - 1);
      if(calculateDelta(above,startPixel) <=tolerance_){ 
        stack.push(Point(x,y - 1));
      }
  }
  
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */

    while((!empty()) && visited[stack.top().x][stack.top().y] == true) {
      stack.pop();
  }
    if(empty()) return Point(0,0);
    Point topPoint = stack.top();
    visited[topPoint.x][topPoint.y] = true;
    stack.pop();
    
    return topPoint;

}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() {
  /** @todo [Part 1] */
  while((!empty()) && visited[stack.top().x][stack.top().y] == true) {
      stack.pop();
  }
  if(!empty())
  return stack.top();
  else return Point(0,0);
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return stack.empty();
}
