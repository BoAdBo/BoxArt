#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
using std::cout;
using std::list;
/**
 * Definition for a binary tree node.
 * strict TreeNode {
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

class Solution {
  list<int> temp;
public:
  /* This is min heap... stupid*/
  // bool isValidBST(TreeNode* root) {
  //   if(root != NULL) {
  //     bool cur = false;
  //     if(root->left != NULL && root->right != NULL) {
  //       cur = (root->left->val < root->val && root->right->val > root->val);
  //     }
  //     else if(root->right != NULL) {
  //       cur = (root->right->val > root->val);
  //     }
  //     else if(root->left != NULL) {
  //       cur = (root->left->val < root->val);
  //     }
  //     else {
  //       return true;
  //     }
  //     return (cur && isValidBST(root->left) && isValidBST(root->right));
  //   }
  //   else {
  //     return true;
  //   }
  // }

  /*
    return (left, root->val, right) list
  */
  list<int> helper(TreeNode *root) {
    if(root != NULL) {
      list<int> left = helper(root->left);
      list<int> mid = list<int>(1, root->val);
      list<int> right = helper(root->right);
      left.splice(left.end(), mid);
      left.splice(left.end(), right);
      return left;
    }
    else {
      return list<int>();// as nothing
    }
  }
  bool isValidBST(TreeNode *root) {
    temp = helper(root);
    list<int>::const_iterator i = temp.begin();
    int last = *i;
    i++;
    while(i != temp.end()) {
      if(last >= *i) {
        return false;
      }
      last = *i;
      i++;
    }
    return true;
  }
};

// int main() {
//   TreeNode root(0);
//   //TreeNode left(1);
//   TreeNode right(-1);
//   //root.left = &left;
//   root.right = &right;
//   Solution test;
//   //cout << test.isValidBST(&root);
//   list<int> t = test.helper(&root);
//   list<int>::const_iterator i = t.begin();
//   while(i != t.end()) {
//     cout << *i << " ";
//     ++i;
//   }
//   cout << "\n";
//   cout << test.isValidBST(&root);
// }
