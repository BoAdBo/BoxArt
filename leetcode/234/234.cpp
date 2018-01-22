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

class Solution1 {
public:
  static bool isPalindrome(ListNode* head) {
    ListNode *iter = head;
    int count = 0;
    if(head == NULL) return true;

    while(iter != NULL) {
      iter = iter->next;
      count++;
    }

    ListNode *half = head;
    for(int i = 0; i < count / 2; ++ i) {
      half = half->next;
    }

    while(half != NULL) {
      if(head->val != half->val) return false;
      head = head->next;
      half = half->next;
    }

    return true;
  }
};

#include <stdio.h>
class Solution : public Solution1 {
};

int main() {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(1);
  if(Solution::isPalindrome(head)) {
    printf("it is");
  }
  else {
    printf("it is not");
  }
}
