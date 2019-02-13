/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    int n = k;
    ListNode* first = head;
    ListNode* last = head;
    // the node of the previous end of sub group
    ListNode* prev;

    // finds the next n elements
    while (last != nullptr && n > 0) {
      last = last->next;
      --n;
    }

    // out of range
    if (last == nullptr && n > 0) return head;

    // reverse the sub group
    head = reverse(first, last);
    // first now becomes the end of linked list
    prev = first;

    while (true) {
      first = last;
      n = k;
      while (last != nullptr && n > 0) {
        last = last->next;
        --n;
      }

      if (last == nullptr && n > 0) return head;
      ListNode* new_head = reverse(first, last);
      prev->next = new_head;
      prev = first;
    }
  }

  // reverse the linked list and return its new head
  // last is the x->next, where x is the last node of the original linked list
  // and after reverse, x becomes the first
  ListNode* reverse(ListNode* first, ListNode* last) {
    ListNode* prev = last;
    ListNode* curr = first;
    ListNode* next;
    while (curr != last) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    return prev;
  }
};
