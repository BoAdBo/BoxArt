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
  ListNode* reverseBetween(ListNode* head, int m, int n) {
    int counter = 2;
    while (counter < m) {
      head = head->next;
      ++counter;
    }

    // the start
    ListNode* prev = head->next;
    ListNode* cur = prev->next;
    ListNode* next; //; = cur->next;
    while (counter < n) {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
      ++counter;
      std::cout << counter << ' ' << n << '\n';
    }

    head->next->next = prev->next;
    head->next = prev;
    return head;
  }

  void reverse(ListNode* first, ListNode* last) {
    ListNode* q = first;
    ListNode* p = first->next;
    ListNode* n = p->next;
    while (p != last) {
      n = p->next;
      p->next = q;
      q = p;
      p = n;
    }
    first->next = p;
  }
  // ListNode* reverseBetween(ListNode* head, int m, int n) {
  //   int counter = 1;
  //   ListNode* iter = head;
  //   while (counter < m) {
  //     iter = iter->next;
  //     ++counter;
  //   }
  //   ListNode* mid = iter;
  //   std::stack<int> vals;
  //   while (counter <= n) {
  //     vals.push(iter->val);
  //     iter = iter->next;
  //     ++counter;
  //   }

  //   while (mid != iter) {
  //     mid->val = vals.top();
  //     vals.pop();
  //     mid = mid->next;
  //   }

  //   return head;
  // }
};
