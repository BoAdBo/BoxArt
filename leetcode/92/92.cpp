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
    ListNode* begin;
    int counter = 0;
    ListNode tmp = ListNode(-1);
    tmp.next = head;
    begin = &tmp;

    // locate the start - 1
    while (counter < m-1) {
      begin = begin->next;
      ++counter;
    }

    // the start
    ListNode* prev = begin->next;
    ListNode* curr = prev->next;
    ListNode* next; //; = cur->next;
    counter += 2; // location based on curr
    while (counter < n+1) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
      ++counter;
    }

    begin->next->next = curr;
    begin->next = prev;
    if (m == 1) {
      return prev;
    }

    return head;
  }

  ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode* curr = head;
    ListNode* prev = nullptr;
    while (m > 1) {
      prev = curr;
      curr = curr->next;
      --m;
      --n;
    }

    ListNode* con = prev;
    ListNode* tail = curr;
    ListNode* next;
    while (n > 0) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
      --n;
    }

    if (con != nullptr) {
      con->next = prev;
    } else {
      head = prev;
    }

    tail->next = curr;
    return head;
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
