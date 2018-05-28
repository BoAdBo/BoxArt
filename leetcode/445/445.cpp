/**

 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    stack<int> a1, a2;

    ListNode *iter1 = l1, *iter2 = l2;
    while( iter1 ) {
      a1.push(iter1->val);
      iter1 = iter1->next;
    }
    while( iter2 ) {
      a2.push(iter2->val);
      iter2 = iter2->next;
    }

    std::vector<int> res_from_back;
    res_from_back.reserve(max(a1.size(), a2.size()));
    int carry = 0;
    while( !a2.empty() && !a1.empty() ) {
      int val1 = a1.top(); a1.pop();
      int val2 = a2.top(); a2.pop();
      int sum = val1 + val2 + carry;
      carry = sum / 10;
      res_from_back.emplace_back(sum % 10);
    }

    if ( a1.empty() ) {
      while( !a2.empty() ) {
        int val1 = a2.top(); a2.pop();
        int val2 = carry;
        int sum = val1 + val2;
        res_from_back.emplace_back(sum % 10);
        carry = sum / 10;
      }
    }

    if ( a2.empty() ) {
      while( !a1.empty() ) {
        int val1 = a1.top(); a1.pop();
        int val2 = carry;
        int sum = val1 + val2;
        res_from_back.emplace_back(sum % 10);
        carry = sum / 10;
      }
    }

    if ( carry > 0 ) {
      res_from_back.emplace_back(carry);
    }

    ListNode *head = new ListNode(res_from_back[res_from_back.size()-1]);
    ListNode *iter = head;
    int i = res_from_back.size() - 1;
    // unsigned integer is always larger or greater than 0 mate
    while ( --i >= 0 ) {
      iter->next = new ListNode(res_from_back[i]);
      iter = iter->next;
    }

    return head;
  }
};
