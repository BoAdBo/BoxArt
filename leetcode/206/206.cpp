
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* reverseList(ListNode* head) {

    // given as the head of the new list
    if ( !(head) || !(head->next) ) return head;
    ListNode *new_head = reverseList(head->next);
    ListNode *new_tail = head->next;
    new_tail->next = head;
    head->next = NULL;
    return new_head;
  }

  ListNode* reverseList(ListNode* head) {
    return reverse(head, nullptr);
  }

  ListNode* reverse(ListNode* first, ListNode* last) {
    ListNode* prev = last;
    ListNode* curr = first;
    ListNode* next = last;

    while (curr != last) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }

    return prev;
  }
};
