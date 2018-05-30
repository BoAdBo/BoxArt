
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
};
