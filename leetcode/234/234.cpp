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
    
  }
};

class Solution : public Solution1 {
};

#include <stdio.h>

int main() {
  ListNode *head = new ListNode(1);
  //head->next = new ListNode(2);
  //head->next->next = new ListNode(1);
  if(Solution::isPalindrome(head)) {
    printf("it is");
  }
  else {
    printf("it is not");
  }
}
