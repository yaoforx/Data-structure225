template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode * curr1 = first;
  ListNode * curr2 = second;
  if (first == NULL)
  {
    return second;
  }
  if (second == NULL)
  {
    return first;
  }
  if (curr2->data < curr1->data)
  {
    curr1->prev = curr2;
    second = curr2->next;
    if (second != NULL)
      second->prev = NULL;
    curr2->next = curr1;
    first = curr2;
    curr2 = second;
  }
  while (second != NULL)
  {
    if (curr2->data < curr1->data)
    {
      second = curr2->next;
      curr1->prev->next = curr2;
      curr2->prev = curr1->prev;
      curr2->next = curr1;
      curr1->prev = curr2;
      curr2 = second;
    }
    else if (curr1->next != NULL)
    {
      curr1 = curr1->next;
    }
    else
    {
      curr1->next = curr2;
      curr2->prev = curr1;
      second = NULL;
    }
  }
  return first;
}
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  
 
  ListNode * node1 = first;
  ListNode * node2 = second;
  ListNode * temp = first;
  if(first == NULL) return second;
  if(second == NULL) return first;
  while(second != NULL) {
    node2 = second;
    second = second->next;
    node2->next = NULL;
    node2->prev = NULL;
    if(node2->data < first->data) {
        node2->next = first;
        first->prev = node2;
        node2->prev = NULL;
        first = node2;
        node1 = first;
        continue;
    }
    label:
    if(node1->next == NULL) {

      node1->next = node2;
      node2->prev = node1;
      node1 = node1->next;
    }
    else if (node1->next->data < (node2->data)){
      node1 = node1->next;
      goto label;
    }
    else {
      temp = node1->next;
      node1->next = node2;
      node2->prev = node1;
      node2->next = temp;
      temp->prev = node2;
    }

  }


  return first;
  
  }


  ListNode * node1 = first;
  ListNode * node2 = second;
  ListNode * temp = first;
  if(first == NULL) return second;
  if(second == NULL) return first;
  if(node2->data < node1->data) {
    node1->prev = node2;
    second = node2->next;
    if(second != NULL) 
    second->prev = NULL;
    node2->next = node1;
    first = node2;
    node2 = second;
    node1 = first;
  }
  while(second != NULL) {
    
  
    if(node2->data < node1->data) {
        node1->prev->next = node2;
        second = node2->next;
        node2->prev = node1->prev;
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


