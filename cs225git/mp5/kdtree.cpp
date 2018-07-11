/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

// my include
#include "point.h"
#include "kdtree.h"
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if(first[curDim] < second[curDim]) return true;
    else if(first[curDim] == second[curDim]) return first < second;
    else return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double future = 0;
    double current = 0;
    for(unsigned i = 0; i < Dim; i++) {
        current += (currentBest[i] - target[i])*(currentBest[i] - target[i]);
        future  += (potential[i] - target[i])*(potential[i] - target[i]);
    }
    if(current < future ) return false;
    else if(future == current ) return potential < currentBest;
    else return true;
}
//------------------------------------------------------------------------------
//These two functions were written based on Quick Select partition alorithms
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& list, int left, int right, int pivotIndex, unsigned height) {
    Point<Dim> pivotValue = list[pivotIndex];
    //swap pivotIndex and the very right element
    Point<Dim> temp = list[pivotIndex];
    list[pivotIndex] = list[right];
    list[right] = temp;
    int storeIndex = left;
    for(int i = left ; i <= right - 1; i++) {
        if(smallerDimVal(list[i],pivotValue,height%Dim)) {
           //swap
            Point<Dim> temp = list[storeIndex];
            list[storeIndex] = list[i];
            list[i] = temp;
            storeIndex++;
        }

    }
    Point<Dim> t = list[right];
    list[right] = list[storeIndex];
    list[storeIndex] = t;
    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int left, int right, unsigned height, int k) {
    if(left == right) return list[left];
    int pivotIndex =  rand() % (right - left) + left;//randomly choose a pivot index between left and right
    pivotIndex = partition(list,left,right,pivotIndex,height);
    //k is median index in this region
    if( k == pivotIndex) return list[k];
    else if (k < pivotIndex) return  quickSelect(list,left,pivotIndex - 1,height,k);
    else return quickSelect(list, pivotIndex + 1, right,height, k);
}
//------------------------------------------------------------------------------------
//This function help to build tree recursively
template <int Dim>
void KDTree<Dim>::KDTreeHelper(vector<Point<Dim>>& list, int left, int right, int h, KDTreeNode *& root) {
    if (left > right) return;
    int mid = floor((left + right)/2);
    root = new KDTreeNode(quickSelect(list, left, right, h, mid));
    if(left == right) return;
    KDTreeHelper(list, left, mid-1, h + 1, root->left);
    KDTreeHelper(list, mid+1, right, h + 1, root->right);

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    root = NULL;
    if(newPoints.size() == 0) return;
    size_t sizeOfArr = newPoints.size();
    int h = 0;
    vector<Point<Dim>> list = newPoints;

    KDTreeHelper(list, 0 , sizeOfArr -1 , h, root);

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */

    root = copy(other.root);
    size = other.size;

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
        size = rhs.size;
    }
    return *this;

}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * subroot) {
    if (subroot == NULL)
        return;
    clear(subroot->left);
    clear(subroot->right);
    delete subroot;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::copy(const KDTreeNode * subroot)
{
    if (subroot == NULL)
        return NULL;

    // Copy this node and it's children
    struct  KDTreeNode * newNode = new KDTreeNode(subroot->point);
    newNode->left = copy(subroot->left);
    newNode->right = copy(subroot->right);
    return newNode;

}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
    if (root != NULL) {
        clear(root);
        root = NULL;
        size = 0;
    }
}

/*This function calculate distance in certain Dim*/
template <int Dim>
long KDTree<Dim>::dimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{

    return (first[curDim] - second[curDim]) * (first[curDim] - second[curDim]);

}
/*This function calculate distance between 2 points*/
template <int Dim>
long KDTree<Dim>::distance(const Point<Dim>& target,
                                const Point<Dim>& currentBest) const
{


    long current = 0;
    for(unsigned i = 0; i < Dim; i++) {
        current += (currentBest[i] - target[i])*(currentBest[i] - target[i]);

    }
    return current;

}

template <int Dim>
Point<Dim> KDTree<Dim>::helpToFindNearest(const Point<Dim>& query, KDTreeNode* subroot, int height) const {
    // this distance calculates the distance between target and current Best node
    Point<Dim> currentBest;
    Point<Dim> potential;
    //return if it is a leaf
    if (subroot->left == NULL && subroot->right == NULL) return subroot->point;
    // decide to go left subtree or right subtree based on SmallerDim
    if(smallerDimVal(query, subroot->point, height % Dim)) {
        if(subroot->left != NULL)
            currentBest = helpToFindNearest(query, subroot->left, height + 1);
    }
    else {
        if (subroot->right != NULL)
            currentBest = helpToFindNearest(query, subroot->right, height + 1);

    }
    //check if the subroot is better
    if (shouldReplace(query, currentBest, subroot->point)) currentBest = subroot->point;
    //check if the other subtree is potentially better
    if(smallerDimVal(query, subroot->point, height % Dim)) {
        if (subroot->right != NULL && dimVal(subroot->point, query, height % Dim) <= distance(currentBest, query)) {
            potential = helpToFindNearest(query, subroot->right, height + 1);
        }
        else return currentBest;


    }
    else {
        if (subroot->left != NULL && dimVal(subroot->point, query, height % Dim) <= distance(currentBest, query)) {
            potential = helpToFindNearest(query, subroot->left, height + 1);

        }
        else return currentBest;

    }

    if (shouldReplace(query, currentBest, potential)) currentBest = potential;

    return currentBest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return helpToFindNearest(query, root, 0);
}

