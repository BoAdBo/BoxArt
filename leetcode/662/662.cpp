#include <list>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
using std::cout;
using std::list;
using std::vector;
using std::queue;
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

class Solution {
public:
  int widthOfBinaryTree(TreeNode* root) {
    // BFS, two queues
    queue<TreeNode*> qu1, qu2;
    unsigned int max = 0;
    qu1.push(root);
    queue<TreeNode*> *next = &qu2;
    queue<TreeNode*> *current = &qu1;

    while(!(*current).empty()) {

      int last_not_null = 0;
      int index = 0;
      while(!(*current).empty()) {
        TreeNode * node = (*current).front();
        if(node != NULL) {
          last_not_null = index;
          (*next).push(node->left);
          (*next).push(node->right);
        }
        index++;
        (*current).pop();
      }
      if(max < last_not_null + 1) {
        max = last_not_null+1;
      }
      // swap current and next
      queue<TreeNode*> *temp = current;
      current = next;
      next = temp;
      // next iteration
    }
    return max;
  }

};

int main() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(3);
  root->right = new TreeNode(2);
  Solution test;
  cout << test.widthOfBinaryTree(root);
}
