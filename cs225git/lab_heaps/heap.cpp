
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <iostream>
#include "heap.h"
template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return (currentIdx * 2 + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return (currentIdx * 2 + 2);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.

    return (currentIdx - 1)/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(!_elems[leftChild(currentIdx)].empty()) return true;
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    int l = leftChild(currentIdx);
    int r = rightChild(currentIdx);
    int smallest = currentIdx;
    if(l < _elems.size() && _elems[l] < _elems[currentIdx])
        smallest = l;
    if(r < _elems.size() && _elems[r] < _elems[smallest])
        smallest = r;

    return smallest;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx) {
    // @TODO Implement the heapifyDown algorithm.
    size_t l = leftChild(currentIdx);
    size_t r = rightChild(currentIdx);
    size_t smallest= currentIdx;
    if(l < _elems.size() && _elems[l] < _elems[currentIdx])
        smallest = l;
    if(r < _elems.size() && _elems[r] < _elems[smallest])
        smallest= r;
    if(smallest != currentIdx) {
        std::swap(_elems[currentIdx],_elems[smallest]);
        heapifyDown(smallest);
    }
}

template <class T, class Compare>
void heap<T, Compare>:: heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems = elems;
    for(int i = _elems.size()/2; i >= 0; i--) {
        heapifyDown(i);
    }

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if(_elems.size() == 1) {
        int temp = _elems[0];
        _elems.pop_back();
        return temp;
    }
    int temp = _elems[0];
    std::swap(_elems[0],_elems[_elems.size() - 1]);

    _elems.pop_back();

    heapifyDown(0);



    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority

    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap

    _elems.push_back(elem);
    int i = _elems.size() - 1;
    while(i != 0 && _elems[parent(i)] > _elems[i]) {
        std::swap(_elems[i],_elems[parent(i)]);
        i = parent(i);
    }
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size() == 1)
    return true;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}


