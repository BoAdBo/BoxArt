#include <limits.h>
#include <stdlib.h>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// class Solution {
// public:
//   bool isSameTree(TreeNode* p, TreeNode* q) {
//     if(p == NULL && q == NULL) return true;
//     else if(p != NULL && q != NULL) {
//       if (p->val != q->val) {
//         return false;
//       }
//       return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
//     }
//     else {
//       return false;
//     }
//   }
// };


class Solution {
public:
  bool isSameTree(TreeNode* p, TreeNode* q) {
    if(!p && !q) return true;
    else if(p && q) {
      return (p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
    }
    else {
      return false;
    }
  }
};


#include <iostream>
using std::cout;

int main() {
  TreeNode *p = new TreeNode(1);
  p->left = new TreeNode(2);

  TreeNode *q = new TreeNode(1);
  q->right = new TreeNode(2);
  Solution test;
  cout << test.isSameTree(p, q);
}
