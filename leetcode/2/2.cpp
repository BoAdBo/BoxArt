/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <stdlib.h>


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *sum = new ListNode(0);
    ListNode *head = sum;

    int acc = 0;
    while(l1 != NULL && l2 != NULL) {
      sum->next = new ListNode(0);
      sum = sum->next;
      acc = l1->val + l2->val + acc;
      sum->val = acc % 10;
      acc /= 10;
      l1 = l1->next;
      l2 = l2->next;
    }
    ListNode *p;
    if(l1 != NULL) p = l1;
    else p = l2;

    while(p != NULL) {
      sum->next = new ListNode(0);
      sum = sum->next;
      acc = p->val + acc;
      sum->val = acc % 10;
      acc /= 10;
      p = p->next;
    }
    if(acc != 0) sum->next = new ListNode(acc);

    return head->next;
  }
};
