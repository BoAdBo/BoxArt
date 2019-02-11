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
  // using the access pattern
  // void reorderList(ListNode* head) {
  //   if (head == nullptr) return;
  //   ListNode* curr = head;
  //   std::vector<ListNode*> storage;
  //   while (curr != nullptr) {
  //     storage.push_back(curr);
  //     curr = curr->next;
  //   }

  //   int shift = storage.size() - 1;
  //   int sign = 1;
  //   int prev = 0, next = shift;
  //   for (int i = 0; i < storage.size() - 1; ++ i) {
  //     storage[prev]->next = storage[next];
  //     // std::cout << prev << ':' << next << '\n';
  //     sign = -sign;
  //     --shift;
  //     prev = next;
  //     next = next + sign * shift;
  //   }
  //   storage[prev]->next = nullptr;
  // }

  void reorderList(ListNode* head) {
    if (head == nullptr) return;
    ListNode* curr = head;
    std::vector<ListNode*> storage;
    while (curr != nullptr) {
      storage.push_back(curr);
      curr = curr->next;
    }

    if (storage.size() % 2 != 0) {
      int i = 0, j = storage.size()-1;
      for (; i != j; ) {
        storage[i]->next = storage[j];
        ++i;
        storage[j]->next = storage[i];
        --j;
      }
      storage[i]->next = nullptr;
    }
    else {
      int i = 0, j = storage.size()-1;
      for (; ;) {
        storage[i]->next = storage[j];
        ++i;
        if (i == j) break;
        storage[j]->next = storage[i];
        --j;
      }
      storage[i]->next = nullptr;
    }

  }

};
