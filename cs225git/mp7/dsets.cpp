/* Your code here! */
#include "dsets.h"

DisjointSets::DisjointSets() {
}

DisjointSets::DisjointSets(int num) {
	elements = vector<int>(num);
	for (auto & element : elements) {
		element = -1;
	}
}

//Creates n unconnected root nodes at the end of the vector.
//Parameters
//num	The number of nodes to create
void DisjointSets::addelements(int num) {
	for (int i=0; i<num; i++)
	{
		elements.push_back(-1);
	}
}


//This function should compress paths and works as described in lecture.
//Returns
//the index of the root of the up-tree in which the parameter element resides.
int DisjointSets::find(int elem) {
	if (elements[elem] < 0)
		return elem;
	else { 
		int root = find(elements[elem]);
		elements[elem] = root;
		return root;
	}
}

//This function should be implemented as union-by-size.
//That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger. 
//This function works as described in lecture, except that you should not assume that the arguments to setunion are roots of existing uptrees.
//Your setunion function SHOULD find the roots of its arguments before combining the trees. 
//If the two sets are the same size, make the tree containing the second argument point to the tree containing the first. 
//(Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)
//Parameters
//a	Index of the first element to union
//b	Index of the second element to union
void DisjointSets::setunion(int a, int b) {
	int root1 = find(a);
	int root2 = find(b);
	int size1 = -1*elements[root1];
	int size2 = -1*elements[root2];
	int newsize = size1 + size2;
	if (size1 > size2)
	{
		elements[root2] = root1;
		elements[root1] = -1*newsize;
	}
	else
	{
		elements[root1] = root2;
		elements[root2] = -1*newsize;
	}
}

int DisjointSets::size(int elem) {
	int i = find(elem);
	return -1*elements[i];
}
