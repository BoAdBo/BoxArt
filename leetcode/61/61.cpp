struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {

public:
  ListNode* rotateBy1(ListNode *head) {
    ListNode *iter = head;
    // if the list has only one element or zero element
    if ( iter == NULL || iter->next == NULL ) {
      return iter;
    }

    // find the element before the last element
    while ( iter->next->next != NULL ) {
      iter = iter->next;
    }

    // perform rotate by 1
    ListNode *new_head = iter->next;
    new_head->next = head;
    iter->next = NULL;

    // return new head
    return new_head;
  }

  ListNode* rotateRight(ListNode *head, int k) {
    // iterate from reverse, keep a vector
    std::vector<ListNode *> vector_form;
    vector_form.reserve(1000);
    ListNode *iter = head;
    while ( iter != NULL ) {
      vector_form.emplace_back(iter);
      iter = iter->next;
    }

    // do nothing if there is zero or 1 element
    if ( vector_form.size() == 0 || vector_form.size() == 1)
      { return head; }

    // pick the (kth mod size) element counting from the back
    // and perform rotate
    // if actual movement is 0, do nothing
    int actual_k = k % vector_form.size();
    if ( actual_k == 0 ) { return head; }

    // index from back
    size_t index = vector_form.size() - actual_k - 1;

    // find the new head and the new tail
    ListNode *new_tail = vector_form[index];
    ListNode *new_head = new_tail->next;
    // last element should connect back to original head
    vector_form[vector_form.size() - 1]->next = head;
    new_tail->next = NULL;

    // // rotate by k
    // ListNode *new_head = head;
    // while( k-- > 0 ) {
    //   // find the last element
    //   new_head = rotateBy1(new_head);
    // }
    return new_head;
  }
};
