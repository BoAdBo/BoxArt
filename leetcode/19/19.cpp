
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// class Solution {
// public:

//   // would leak memory? although this isn't allocated on heap
//   // ListNode* removeNthFromEnd(ListNode* head, int n) {
//   //   std::vector<ListNode *> vector_form;
//   //   vector_form.reserve(100);

//   //   ListNode *iter = head;
//   //   while( iter ) {
//   //     vector_form.emplace_back(iter);
//   //     iter = iter->next;
//   //   }

//   //   std::size_t index = vector_form.size() - n;
//   //   // if delete the first element
//   //   if ( !index )
//   //     { return head->next; }

//   //   ListNode *to_be_del = vector_form[index];
//   //   ListNode *node_before = vector_form[vector_form.size() - n - 1];
//   //   // simply link the next element
//   //   node_before->next = to_be_del->next;
//   //   return head;
//   // }
//   ListNode *removeNthFromEnd(ListNode *head, int n) {

//     ListNode *iter = head;
//     int size = 0;
//     while( iter ) {
//       ++size;
//       iter = iter->next;
//     }

//     // get the index of the deleted element
//     int index = size - n;
//     // if deleting the first element
//     if ( !index )
//       return head->next;

//     iter = head;

//     // find the element before the deleted element
//     while( --index ) {
//       iter = iter->next;
//     }

//     iter->next = iter->next->next;
//     return head;
//   }
// };
class Solution {
public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    // t2 用于 计数 t1 才是关键
    ListNode** t1 = &head, *t2 = head;
    for(int i = 1; i < n; ++i)
      {
        t2 = t2->next;

      }

    while(t2->next != NULL)
      {
        t1 = &((*t1)->next);
        t2 = t2->next;
      }
    *t1 = (*t1)->next;
    // although head is copied into the function
    // but if the head is to be deleted
    // it would return the next element of the head

    // ListNode ** would actually be referencing the actual address of the
    // next field if head->next is performed
    return head;

  }
};
