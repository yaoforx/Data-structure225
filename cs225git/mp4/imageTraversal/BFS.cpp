#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance)   
: start_(start), png_(png),tolerance_(tolerance) {
  /** @todo [Part 1] */
  
  queue.push(start);
  startX = start.x;
  startY = start.y;
  
  unsigned int row = png.height();
  unsigned int col = png.width();
  visited.resize(col,vector<bool>(row));
  for(unsigned int i = 0; i < col; i++)
    for(unsigned int j = 0; j < row; j++){
      visited[i][j] = false;
    }
    visited[startX][startY] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS * bfs = new BFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*bfs,start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  unsigned int x = point.x;
  unsigned int y = point.y;
  HSLAPixel & startPixel = png_.getPixel(startX,startY);


  if (x + 1 < png_.width() && !visited[x+1][y]) 
    { 
      HSLAPixel & right = png_.getPixel(x + 1,y);
      if(calculateDelta(right,startPixel) <=tolerance_){ 
        queue.push(Point(x+1,y));
        visited[x+1][y] = true;
      }
    }
  if (y + 1 < png_.height() && !visited[x][y+1]) {
        HSLAPixel & right = png_.getPixel(x,y + 1);
      if(calculateDelta(right,startPixel) <=tolerance_){ 
        queue.push(Point(x,y + 1));
        visited[x][y + 1] = true;
      }
  }
  if ((int)x - 1 >= 0 &&  !visited[x - 1][y]) {
       HSLAPixel & right = png_.getPixel(x -1,y);
      if(calculateDelta(right,startPixel) <=tolerance_){ 
        queue.push(Point(x-1,y));
        visited[x-1][y] = true;
      }
  }
  if ((int)y - 1 >= 0 &&  !visited[x][y - 1]) {
       HSLAPixel & right = png_.getPixel(x ,y - 1);
      if(calculateDelta(right,startPixel) <=tolerance_){ 
        queue.push(Point(x,y - 1));
        visited[x][y - 1] = true;
      }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point topPoint = queue.front();
  queue.pop();
  return topPoint;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() {
  /** @todo [Part 1] */
  if(!empty())
  return queue.front();
  else
  return Point(0,0);
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return queue.empty();
}
