#include "predefined.hpp"

static const auto io_sync_off = []()
                                {
                                  std::ios::sync_with_stdio(false);
                                  std::cin.tie(nullptr);
                                  std::cout.tie(nullptr);
                                  return nullptr;
                                }();

class Solution {
public:
  // Naive slow one
  // ListNode* mergeKLists(vector<ListNode*>& lists) {
  //   // OK solution
  //   auto size = lists.size();
  //   ListNode* head = nullptr;
  //   ListNode** iter = &(head);
  //   std::vector<ListNode*> js(size);
  //   for (auto i = 0ul; i < size; ++ i)
  //     js[i] = lists[i];

  //   bool empty = false;
  //   int advancedIndex = -1;
  //   int min = std::numeric_limits<int>::max();

  //   while (!empty) {
  //     empty = true;
  //     for (auto i = 0ul; i < size; ++ i) {
  //       if (js[i] != nullptr && min >= (js[i]->val)) {
  //         min = (js[i]->val);
  //         advancedIndex = i;
  //         empty = false;
  //       }
  //     }
  //     if (empty) break;
  //     *iter = new ListNode(js[advancedIndex]->val);
  //     std::cout << (*iter)->val << '\n';
  //     iter = &((*iter)->next);
  //     js[advancedIndex] = js[advancedIndex]->next;
  //     min = std::numeric_limits<int>::max();
  //     advancedIndex = -1;
  //   }
  //   return head;
  // }
  // struct Cmp {
  //   bool operator() (ListNode* a, ListNode* b) { return a->val > b->val; }
  // };

  // ListNode* mergeKLists(vector<ListNode*>& lists) {
  //   std::priority_queue<ListNode*, std::vector<ListNode*>, Cmp>
  //     pQueue;

  //   ListNode* head = nullptr;
  //   ListNode** iter = &head;
  //   for (const auto &list : lists)
  //     if (list) pQueue.push(list);

  //   while (!pQueue.empty()) {
  //     auto lesser = pQueue.top(); pQueue.pop();
  //     *iter = new ListNode(lesser->val);
  //     iter = &((*iter)->next);
  //     if (lesser->next) {
  //       pQueue.push(lesser->next);
  //     }
  //   }
  //   return head;
  // }

  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) {
      return list2;
    }
    if (list2 == nullptr) {
      return list1;
    }

    if (list1->val < list2->val) {
      list1->next = mergeTwoLists(list1->next, list2);
      return list1;
    }
    else {
      list2->next = mergeTwoLists(list1, list2->next);
      return list2;
    }
  }

  ListNode* mergeLogTwo(std::vector<ListNode*>::iterator begin, std::vector<ListNode*>::iterator end) {
    auto length = std::distance(begin, end);
    auto mid = length / 2;
    if (length <= 1) return *begin;
    else
      return mergeTwoLists(mergeLogTwo(begin, begin+mid),
                           mergeLogTwo(begin+mid, end));
  }

  ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    auto head = mergeLogTwo(lists.begin(), lists.end());
    // iterative
    // while (lists.size() > 1) {
    //   auto head = mergeTwoLists(lists[lists.size()-1], lists[lists.size()-2]);
    //   lists.pop_back();
    //   lists[lists.size()-1] = head;
    // }
    return head;
  }
};
