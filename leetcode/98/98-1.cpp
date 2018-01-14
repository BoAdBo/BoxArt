#include <stdlib.h>
#include <iostream>
#include <vector>
#include <limit.h>
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
public:

  bool isValidBST(TreeNode *root) {
    return isValidBST(root, NULL, NULL);
  }

  bool isValidBST(TreeNode *root, TreeNode *minNode, TreeNode *maxNode) {
    if(root == NULL) return true;
    else if(minNode != NULL && root->val <= minNode->val ||
            maxNode != NULL && root->val >= maxNode->val)
      return false;
    return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
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
