/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
template <class K, class V>
int AVLTree<K, V>::getHeight(const Node* subroot) {
  if (subroot == NULL) {
    return -1;
  }
  return (1 + std::max(getHeight(subroot->left), getHeight(subroot->right)));
}
template <class K, class V>
int AVLTree<K, V>::treeHeight(Node * cur) {
    if(cur == NULL)
        return -1;
    int left = treeHeight(cur->left);
    int right = treeHeight(cur->right);
    return 1 + std::max(left, right);
}
template <class K, class V>
int AVLTree<K, V>::getHeightBalance(Node* root) {

    int left = treeHeight(root->left);
    int right  = treeHeight(root->right);
    return left - right;

}
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here


    Node * r = t->right;
 
    t->right = r->left;

 
    r->left = t;

   
    t = r;
    t->height = max(treeHeight(t->left),treeHeight(t->right)) + 1;
    r->height = max(treeHeight(r->left),treeHeight(r->right)) + 1;


}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{

    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here

    Node * l = t->left;
    t->left = l->right;
    //cout<<t->value<<endl;
    l->right = t;
    t = l;
    //cout<<t->value<<endl;
  
    t->height = max(treeHeight(t->left),treeHeight(t->right)) + 1;
    l->height = max(treeHeight(l->left),treeHeight(l->right)) + 1;




}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& n)
{
    // your code here
    int balance = getHeightBalance(n);
    if (balance == -2) {
        if (getHeight(n->left->left) >= getHeight(n->left->right))
            rotateRight(n);
        else
            rotateLeftRight(n);
    }
    else if (balance == 2) {
        if (getHeight(n->right->right) >= getHeight(n->right->left))
            rotateLeft(n);
        else
           rotateRightLeft(n);
    }
 

      return;  
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
  
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) subtree = new Node(key, value);
    /*else if(subtree->right == NULL && subtree->left == NULL) {
        if(key < subtree->key)
            subtree->left = new Node(key, value);
        else
            subtree->right = new Node(key, value);

    }*/
    else if(subtree->right ==  NULL && key > subtree->key) {
        subtree->right = new Node(key, value);
    }
    else if(subtree->left == NULL && key < subtree->key) {
        subtree->left = new Node(key, value);
    }
    else if( key < subtree->key) {

        insert(subtree->left, key, value);
        
    }
    else if(key > subtree->key) {
        
        insert(subtree->right,key,value);
    }
    
    subtree->height = max(treeHeight(subtree->left),treeHeight(subtree->right)) + 1;
    int balance = getHeightBalance(subtree);
   // rebalance(subtree);
    //if((int)key == 23) return;
    if (balance > 1 && key < subtree->left->key)
        rotateRight(subtree);
 
    // Right Right Case
    else if (balance < -1 && key > subtree->right->key)
       rotateLeft(subtree);
 
    // Left Right Case
    else if (balance > 1 && key > subtree->left->key)
    {
        // = subtree->left;
        rotateLeftRight(subtree);
    }
 
    // Right Left Case
    else if (balance < -1 && key < subtree->right->key)
    {
        //subtree = subtree->right;
        rotateRightLeft(subtree);
    }
    
    /* return the (unchanged) node pointer */

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}
template <class K ,class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::findMax(Node *& root) {
    if(root == NULL) return NULL;
    else if(root->right== NULL) return root;
    else return findMax(root->right);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    Node * temp;
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
                subtree = NULL;


            }
        else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            
            temp = findMax(subtree->left);
            //cout<<temp->key<<endl;
            subtree->value = temp->value;
            subtree->key = temp->key;
            remove(subtree->left,temp->key);

        } else {
            /* one-child remove */
            // your code here

            temp = subtree;
            if(subtree->left!=NULL) 
                subtree = subtree->left;
                

            else if(subtree->right != NULL)
                subtree = subtree->right;

            delete temp;


        }


        // your code here
       
    }

    if(subtree == NULL) return;
    //update height of the subtree
     subtree->height = max(treeHeight(subtree->left),treeHeight(subtree->right)) + 1;
     //update to AVL after deletion
        int balance = getHeightBalance(subtree);
        //Left tree has left subtree

        if (balance > 1 && getHeightBalance(subtree->left) >= 0)
       rotateRight(subtree);
 
    // Left Right Case
        else if (balance > 1 && getHeightBalance(subtree->left) < 0)
    {
        rotateLeftRight(subtree);
    }
 
    // Right Right Case
        else if (balance < -1 && getHeightBalance(subtree->right) <= 0)
        rotateLeft(subtree);
 
    // Right Left Case
        else if (balance < -1 && getHeightBalance(subtree->right) > 0)
        {
        rotateRightLeft(subtree);
        }
 // rebalance(subtree);
 
        return;

}
