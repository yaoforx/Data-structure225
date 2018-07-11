/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
if(head_!=NULL) {
  ListNode * cur = head_;

  ListNode * temp = cur->next;

  while(cur->next!= NULL) {
    

    delete cur;
    cur = temp;
    temp = temp->next;

  }

  delete cur;
}
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
  
 
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  
  ListNode * node = new ListNode(ndata);

  if(!(this->empty())){
    //ListNode * cur = head_;
    //ListNode* prev = NULL;
    node->next = head_;
    node->prev = NULL;
    head_ = node;
    node->next->prev = node;
  }
  else{  
    head_ = node;
    tail_ = head_;
  }
  length_++;
}


/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * node = new ListNode(ndata);
  if(!(this->empty())){
    tail_->next = node; 
    node->prev = tail_;
    tail_ = node;
  }
  else{
    head_ = node;
    tail_ = head_;

  }
  length_++;

}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  ListNode* cur = startPoint;
  ListNode* star_prev = startPoint->prev;
  ListNode* end_next = endPoint->next;
 
  ListNode* curTemp = NULL;
  if(startPoint ==head_ && endPoint == tail_) {
     while(cur != end_next){
      curTemp = cur->prev;
      cur->prev = cur->next;
      cur->next = curTemp;
      cur = cur->prev;
    }
    ListNode * temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
  }
  else{
  while(cur != end_next){
      curTemp = cur->prev;
      cur->prev = cur->next;
      cur->next = curTemp;
      cur = cur->prev;
    }
    if(star_prev == NULL){
      head_= endPoint;
      head_->prev = NULL;
     
    } else{
      star_prev->next = endPoint;
      endPoint->prev = star_prev;
    }

    if(end_next == NULL) {
      tail_ = startPoint;
      startPoint->next = NULL;
      
    } else{
      startPoint->next = end_next;
      end_next->prev = startPoint;
    }
 
  }
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode * startPoint = head_;
  ListNode * temp = startPoint;
  ListNode * endPoint = NULL;
  int remain = this->size();
  while(remain >n){
    for(int i = 0; i < n - 1; i++) {
      temp = temp->next;
    }
    endPoint = temp;
     //std::cout << remain << std::endl;
    reverse(startPoint, endPoint);
    startPoint = startPoint->next;
    temp = startPoint; 
    remain = remain - n;

   }
  
   endPoint = tail_;

   reverse(startPoint,endPoint);

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * cur = head_;
  ListNode * prev = head_;
  ListNode * next = NULL;
  while(cur->next != tail_){
    next = cur->next;
    cur->next = next->next;
    next->next->prev = cur;
    tail_->next = next;
    next->prev = tail_;
    tail_ = next;
    cur = cur->next;
    tail_->next = NULL;

  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode * cur = start;
  if(start == NULL) return NULL;
  if(splitPoint == 0) return head_;
  
  else {

      for(int i = 0; i < splitPoint - 1; i++) {
        cur = cur->next;
      }

  }
  ListNode * head2 = cur->next;
  head2->prev = NULL;
  cur->next = NULL;

  
  return head2;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */

template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  /*ListNode * result = NULL;
  if(first == NULL) return second;
  if(second == NULL) return first;
  if(first->data < second->data) {
    first->next = merge(first->next,second);
    first->next->prev = first;
    first->prev = NULL;
    return first;
  }
  else
  {
    second->next = merge(first,second->next);
    second->next->prev = second;
    second->prev = NULL;
    return second;
  }*/



  ListNode * node1 = first;
  ListNode * node2 = second;
  ListNode * temp = first;
  if(first == NULL) return second;
  if(second == NULL) return first;
  if(node2->data < node1->data) {
    
    second = node2->next;
    if(second != NULL)
    second->prev = NULL;
    node1->prev = node2;
    node2->next = node1;
    first = node2;
    node2 = second;
    node1 = first;
  }
  while(second != NULL) {
    
  
    if(node2->data < node1->data) {
        
        second = node2->next;
        node2->prev = node1->prev;
        node1->prev->next = node2;
        node2->next = node1;
        node1->prev = node2;
        node2 = second;
    }
    else if (node1->next != NULL){
      node1 = node1->next;
    }
    else {
      
      node1->next = node2;
      node2->prev = node1;
      second = NULL;
      
    }
  }
  
  
  return first;
 
}


/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
  
    head_ = mergesort(head_, length_);
    tail_ = head_;

    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode * list1;
  ListNode * list2;
  ListNode * headSum;
  list1 = start;
  int length  = 0;
  if(chainLength <=1) {
    return start;
  }
  length = chainLength;
  chainLength/=2;
   
  list2 = split(list1, chainLength);
  list1 = mergesort(list1,chainLength);

  
  list2 = mergesort(list2,length - chainLength);

  headSum = merge(list1,list2);
 


 
  return headSum;
}
