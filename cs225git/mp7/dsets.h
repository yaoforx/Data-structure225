/* Your code here! */
/**
 * @file dsets.h
 */

#ifndef _DSETS_H_
#define _DSETS_H_

#include <vector>
using namespace std;

class DisjointSets
{
	public:
		DisjointSets ();
		DisjointSets (int num);

		void addelements (int num);
		//Creates n unconnected root nodes at the end of the vector.
 
		int find (int elem);
		//This function should compress paths and works as described in lecture.
 
		void setunion (int a, int b);
		//This function should be implemented as union-by-size.
 
		int size (int elem);

	private:
		vector<int> elements;

};

#endif
