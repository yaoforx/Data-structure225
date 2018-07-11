/* Your code here! */
#include "maze.h"

//No-parameter constructor.
//Creates an empty maze.
SquareMaze::SquareMaze () {
}

//Makes a new SquareMaze of the given height and width.
//If this object already represents a maze it will clear all the existing data before doing so. 
//You will start with a square grid (like graph paper) with the specified height and width. 
//You will select random walls to delete without creating a cycle, until there are no more walls that could be deleted without creating a cycle. 
//Do not delete walls on the perimeter of the grid.
//Hints: You only need to store 2 bits per square: the "down" and "right" walls. The finished maze is always a tree of corridors.)
//Parameters
//width		The width of the SquareMaze (number of cells)
//height	The height of the SquareMaze (number of cells)
void SquareMaze::makeMaze (	int width, int height ) {
	//srand(time(NULL));

	width_ = width;
	height_ = height;
	walls_ = vector<vector<vector<bool>>>(width_);
	for (int i=0; i<width_; i++) {
		walls_[i] = vector<vector<bool>>(height_);
		for (int j=0; j<height_; j++) {
			walls_[i][j] = vector<bool>(2);
			//have walls
			//0 right 1 down
			walls_[i][j][0] = true;
			walls_[i][j][1] = true;
		}
	}

	DisjointSets dset;
	dset.addelements(width_*height_);
	int num_independentsets = width_*height_;

	while (num_independentsets>1) {
		//produce random number
		int random_x = rand() % (width_);
		int random_y = rand() % (height_);
		int random_dir = rand() % 2;
		if (walls_[random_x][random_y][random_dir] == true) {
			int index1 = unroll(random_x, random_y);
			if (random_dir==1 && random_y<height_-1) {
				int index2 = unroll(random_x, random_y+1);
				//check whether already in a same set
				if (dset.find(index1)!=dset.find(index2)) {
					num_independentsets--;
					dset.setunion(index1, index2);
					walls_[random_x][random_y][random_dir] = false;
				}
			}
			else if (random_dir==0 && random_x<width_-1) {
				int index2 = unroll(random_x+1, random_y);
				//check whether already in a same set
				if (dset.find(index1)!=dset.find(index2)) {
					num_independentsets--;
					dset.setunion(index1, index2);
					walls_[random_x][random_y][random_dir] = false;
				}
			}
		}
	}

}

//This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
//For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).
//dir = 0 represents a rightward step (+1 to the x coordinate)
//dir = 1 represents a downward step (+1 to the y coordinate)
//dir = 2 represents a leftward step (-1 to the x coordinate)
//dir = 3 represents an upward step (-1 to the y coordinate)
//You can not step off of the maze or through a wall.
//This function will be very helpful in solving the maze. 
//It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, and to verify your maze solution. 
//So make sure that this function works!
//Parameters
//x	The x coordinate of the current cell
//y	The y coordinate of the current cell
//dir	The desired direction to move from the current cell
//Returns
//whether you can travel in the specified direction
bool SquareMaze::canTravel ( int x, int y, int dir ) const {
	if (!isvalid(x,y)) return false;
	if (dir==0 && isvalid(x+1,y) && walls_[x][y][0]==false) return true;
	else if (dir==1 && isvalid(x,y+1) && walls_[x][y][1]==false) return true;
	else if (dir==2 && isvalid(x-1,y) && walls_[x-1][y][0]==false) return true;
	else if (dir==3 && isvalid(x,y-1) && walls_[x][y-1][1]==false) return true;
	return false;
}

//Sets whether or not the specified wall exists.
//This function should be fast (constant time). 
//You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. 
//setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. 
//Our tests will call setWall to copy a specific maze into your implementation.
//Parameters
//x	The x coordinate of the current cell
//y	The y coordinate of the current cell
//dir	Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel). 
//You only need to support setting the bottom and right walls of every square in the grid.
//exists	true if setting the wall to exist, false otherwise
void SquareMaze::setWall ( int x, int y, int dir, bool exists ) {
	if (isvalid(x,y))
	{
		walls_[x][y][dir] = exists;
	}
}

//Solves this SquareMaze.
//For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), 
//which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.
//Select the square in the bottom row with the largest distance from the origin as the destination of the maze. 
//solveMaze() returns the winning path from the origin to the destination as a vector of integers, 
//where each integer represents the direction of a step, using the same encoding as in canTravel().
//If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.
//Hint: this function should run in time linear in the number of cells in the maze.
//Returns
//a vector of directions taken to solve the maze
vector<int> SquareMaze::solveMaze () {
	vector<int> path = findShortestPath();
	std::reverse(path.begin(),path.end());
	return path;
}

//Draws the maze without the solution.
//First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). 
//where height and width were the arguments to makeMaze. Blacken the entire topmost row and leftmost column of pixels, 
//except the entrance (1,0) through (9,0). For each square in the maze, call its maze coordinates (x,y). 
//If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. 
//If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
//The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.
//Returns
//a PNG of the unsolved SquareMaze
PNG * SquareMaze::drawMaze () const {
	int image_width = width_*10+1;
	int image_height = height_*10+1;
	PNG* mazeImage = new PNG(image_width, image_height);

	HSLAPixel black(0, 0, 0);

	for (int i = 0; i<image_width; i++) {
		if (i<1 || i>9) {
			HSLAPixel & pixel = mazeImage->getPixel(i, 0);
			pixel.s = black.s;
			pixel.h = black.h;
			pixel.l = black.l;
		}
	}
	for (int i = 0; i<image_height; i++) {
		HSLAPixel & pixel = mazeImage->getPixel(0, i);
		pixel.s = black.s;
		pixel.h = black.h;
		pixel.l = black.l;
	}
	for (int x=0; x<width_; x++) {
		for (int y=0; y<height_; y++) {
			if (walls_[x][y][0]) {
				for (int k=0; k<=10; k++) {
					HSLAPixel & pixel = mazeImage->getPixel((x+1)*10, y*10+k);
					pixel.s = black.s;
					pixel.h = black.h;
					pixel.l = black.l;
				}
			}
			if (walls_[x][y][1]) {
				for (int k=0; k<=10; k++) {
					HSLAPixel & pixel = mazeImage->getPixel(x*10+k, (y+1)*10);
					pixel.s = black.s;
					pixel.h = black.h;
					pixel.l = black.l;
				}
			}
		}
	}

	return mazeImage;
}

//This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.
//Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. 
//If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). 
//Then if the second step is right, color pixels (5,15) through (15,15) red. 
//Then if the third step is up, color pixels (15,15) through (15,5) red. 
//Continue in this manner until you get to the end of the solution vector, so that your output looks analogous the above picture.
//Make the exit by undoing the bottom wall of the destination square: 
//call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
//Returns
//a PNG of the solved SquareMaze
PNG * SquareMaze::drawMazeWithSolution () {
	PNG* mazeImage = drawMaze();

	HSLAPixel red(0,1,0.5,1);

	vector<int> path = solveMaze();
	int x = 5;
	int y = 5;
	int i;
	for (int iter = 0; iter < (int)path.size(); iter++) {
		if (path[iter]==0) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pixel = mazeImage->getPixel(x+i, y);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			x += 10;
		}
		else if (path[iter]==1) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pixel = mazeImage->getPixel(x, y+i);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			y += 10;
		}
		else if (path[iter]==2) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pixel = mazeImage->getPixel(x-i, y);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			x -= 10;
		}
		else if (path[iter]==3) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pixel = mazeImage->getPixel(x, y-i);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			y -= 10;
		}
	}
	x -= 5;
	y += 5;
	for (i = 1; i < 10; i++) {
		HSLAPixel & pixel = mazeImage->getPixel(x+i, y);
		pixel.l = 1;
	}
	return mazeImage;


}

//Helper function
bool SquareMaze::isvalid (int x, int y) const {
	return (x>=0)&&(x<width_)&&(y>=0)&&(y<height_);
}

int SquareMaze::unroll(int x, int y) const {
	return x*height_+y;
}

pair<int,int> SquareMaze::roll(int position) const {
	return pair<int,int>( position / height_ , position % height_ );
}

vector<int> SquareMaze::findShortestPath() {
	//distance_map
	vector<int> distance_map = vector<int>(width_*height_, 0);
	//parent_map
	vector<int> parent_map = vector<int>(width_*height_, 0);
	//visited_map
	vector<bool> visited_map = vector<bool>(width_*height_, false);
	//queue
	queue<int> q;
	visited_map[0] = true;
	q.push(0);
	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();
		for (auto & neigh : getAdjacent(vertex)) {
			// unvisited
			if (visited_map[neigh] == false)
			{
				visited_map[neigh] = true;
				q.push(neigh);
				distance_map[neigh] = distance_map[vertex] + 1;
				parent_map[neigh] = vertex;
			}
			// visited
		}
	}
	//find the vertex that is farthest from initial vertex
	int vertex_end = findmaxpath(distance_map);
	vector<int> path;
	//get the path
	while (parent_map[vertex_end]!=vertex_end)
	{
		int direction = getdirection(parent_map[vertex_end], vertex_end);
		path.push_back(direction);
		vertex_end = parent_map[vertex_end];
	}
	return path;
}

vector<int> SquareMaze::getAdjacent(int vertex) {
	vector<int> adjacent;
	pair<int,int> coord = roll(vertex);
	int x = coord.first;
	int y = coord.second;
	if (isvalid(x-1, y) && !walls_[x-1][y][0]) {
		adjacent.push_back(unroll(x-1,y));
	}
	if (isvalid(x+1, y) && !walls_[x][y][0]) {
		adjacent.push_back(unroll(x+1,y));
	}
	if (isvalid(x, y-1) && !walls_[x][y-1][1]) {
		adjacent.push_back(unroll(x,y-1));
	}
	
	if (isvalid(x, y+1) && !walls_[x][y][1]) {
		adjacent.push_back(unroll(x,y+1));
	}
	return adjacent;
}

int SquareMaze::findmaxpath(vector<int>& distance_map) {
	int y = height_ - 1;
	int position_max = unroll(0, y);
	for (int x=0; x<width_; x++) {
		int position = unroll(x, y);
		if (distance_map[position] > distance_map[position_max]) {
			position_max = position;
		}
	}
	return position_max;
}

//dir = 0 represents a rightward step (+1 to the x coordinate)
//dir = 1 represents a downward step (+1 to the y coordinate)
//dir = 2 represents a leftward step (-1 to the x coordinate)
//dir = 3 represents an upward step (-1 to the y coordinate)
int SquareMaze::getdirection(int parent, int vertex) {
	pair<int,int> coord_parent = roll(parent);
	int x_parent = coord_parent.first;
	int y_parent = coord_parent.second;
	pair<int,int> coord_vertex = roll(vertex);
	int x_vertex = coord_vertex.first;
	int y_vertex = coord_vertex.second;
	if (x_parent == x_vertex-1) 
		return 0;
	if (x_parent == x_vertex+1) 
		return 2;
	if (y_parent == y_vertex-1) 
		return 1;
	if (y_parent == y_vertex+1) 
		return 3;
	return int();
}

pair<int,int> SquareMaze::coor(int x, int y) const {
    pair<int,int> res(x,y);
    int image_width = width_*10+1;
    int image_height = height_*10+1;
//    if(y > image_height*0.25 && y < image_height*0.75) {
//        res.first =  0.25* image_width +res.first*0.5;
//    }
    res.first = 0.5*res.first * (res.second +image_width/8*7)/image_height;




    return res;
};


PNG * SquareMaze::drawCreativeMaze()  {
    int image_width = width_*10+1;
    int image_height = height_*10+1;
    int new_width = image_width*0.5;
    PNG* mazeImage = new PNG(image_width, image_height);

    HSLAPixel black(0, 0, 0);

    for (int i = 0; i<image_width; i++) {
        if (i<1 || i>9 ) {
            HSLAPixel & pixel = mazeImage->getPixel(coor(i,0).first, coor(i,0).second);
            pixel.s = black.s;
            pixel.h = black.h;
            pixel.l = black.l;
        }


        /*if((i < 0.24* image_width || i >0.74*image_width - 1) ){
            HSLAPixel & pixel = mazeImage->getPixel(coor(i,0.25*image_height).first, coor(i,0.25*image_height).second);
            pixel.s = black.s;
            pixel.h = black.h;
            pixel.l = black.l;
        }
        if((i < 0.24* image_width|| i > 0.74*image_width  - 1)) {
            HSLAPixel & pixel = mazeImage->getPixel(coor(i,0.75*image_height+ 1).first, coor(i,0.75*image_height + 1).second);
            pixel.s = black.s;
            pixel.h = black.h;
            pixel.l = black.l;
        }
*/
    }
    for (int i = 0; i<image_height; i++) {
        HSLAPixel & pixel = mazeImage->getPixel(coor(0, i).first,coor(0,i).second);
        pixel.s = black.s;
        pixel.h = black.h;
        pixel.l = black.l;

    }

    for (int i = 0; i<image_height; i++) {
        if (i< 0.25 * image_height || i> 0.75 * image_height) {
            HSLAPixel & pixel = mazeImage->getPixel(coor(0,i).first,coor(0,i).second);
            pixel.s = black.s;
            pixel.h = black.h;
            pixel.l = black.l;
        }


    }


    for (int x=0; x<width_; x++) {
        for (int y=0; y<height_; y++) {

                if (walls_[x][y][0]) {
                    for (int k = 0; k <= 10; k++) {
                        HSLAPixel &pixel = mazeImage->getPixel(coor((x + 1) * 10,y * 10 + k).first, coor((x + 1) * 10,y * 10 + k).second);
                        pixel.s = black.s;
                        pixel.h = black.h;
                        pixel.l = black.l;
                    }
                }
                if (walls_[x][y][1]) {
                    for (int k = 0; k <= 10; k++) {
                        HSLAPixel &pixel = mazeImage->getPixel(coor(x * 10 + k, (y + 1) * 10).first,coor(x * 10 + k, (y + 1) * 10).second);
                        pixel.s = black.s;
                        pixel.h = black.h;
                        pixel.l = black.l;
                    }
                }

        }
    }


    return mazeImage;
}
PNG * SquareMaze::drawMazeWithSolutionCreative() {

        PNG* mazeImage = drawCreativeMaze();

        HSLAPixel red(0,1,0.5,1);

        vector<int> path = solveMaze();
        int x = 5;
        int y = 5;
        int i;
        for (int iter = 0; iter < (int)path.size(); iter++) {
        if (path[iter]==0) {
                for (i = 0; i <= 10; i++) {
                HSLAPixel & pixel = mazeImage->getPixel(coor(x+i,y).first, coor(x+i,y).second);
                pixel.s = red.s;
                pixel.h = red.h;
                pixel.l = red.l;
            }
        x += 10;
        }
        else if (path[iter]==1) {
            for (i = 0; i <= 10; i++) {
                HSLAPixel & pixel = mazeImage->getPixel(coor(x,y+i).first, coor(x,y+i).second);
                pixel.s = red.s;
                pixel.h = red.h;
                pixel.l = red.l;
            }
        y += 10;
        }
        else if (path[iter]==2) {
            for (i = 0; i <= 10; i++) {
                HSLAPixel & pixel = mazeImage->getPixel(coor(x-i,y).first, coor(x-i,y).second);
                pixel.s = red.s;
                pixel.h = red.h;
                pixel.l = red.l;
            }
        x -= 10;
        }
        else if (path[iter]==3) {
            for (i = 0; i <= 10; i++) {
                HSLAPixel & pixel = mazeImage->getPixel(coor(x,y-i).first, coor(x,y-i).second);
                pixel.s = red.s;
                pixel.h = red.h;
                pixel.l = red.l;
                }
            y -= 10;
            }
        }
        x -= 5;
        y += 5;
        for (i = 1; i < 10; i++) {
            HSLAPixel & pixel = mazeImage->getPixel(coor(x+i,y).first, coor(x+i,y).second);
            pixel.l = 1;
            }
        return mazeImage;


}