/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <utility>
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <algorithm>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}
/*private mirro helper function*/
template <typename T>
void BinaryTree<T>::mirror(Node* root) const{
    if (root == NULL)
        return;
    BinaryTree<T>::Node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);

}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T> 
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<int> iot = root;
    int prev = 0;
    for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
        if(prev > (*it)->elem)
            return false;
        prev = (*it)->elem;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
//User defined helper function for isOrderedRecursive
template <typename T>
bool BinaryTree<T>::isBSTutil(struct Node *node, int min, int max) const{

    if(node == NULL) return true;
    if(node->elem < min || node->elem > max) return false;
    return isBSTutil(node->left, min, node->elem -1) &&
    isBSTutil(node->right, node->elem + 1, max);

}
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{

    // your code here
    Node * iot = root;
    return (isBSTutil(iot, INT_MIN, INT_MAX));
   
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
/*private helperFunction for print paths*/
template <typename T>
void BinaryTree<T>::printPaths(Node* root,vector<vector<T>> &paths, vector<int> row) const {
    //if(root== NULL) return;
    if(!root->left && !root->right) {
        row.push_back(root->elem);
        paths.push_back(row);
        return;
    }
    row.push_back(root->elem);
    if(root->left) printPaths(root->left, paths, row);    
    if(root->right) printPaths(root->right, paths, row);
   
    row.pop_back();

}
    
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T>> &paths) const
{
   
    vector<int> row;
    int sum = 0;
    
    printPaths(root,paths,row);
    
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
/*private helperFunction for sumDistances*/
template <typename T>
int BinaryTree<T>::sumDistances(Node * root, int sum) const
{
  
    if(root == NULL) {

        return 0;
    }
    
   
  return sum+sumDistances(root->left, sum+1)+sumDistances(root->right,sum+1);

}
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    

   int sum = 0;
    

    return sumDistances(root,sum);
}


