#include <list>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <map>
using std::map;
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

// class Solution {
// public:
//   int widthOfBinaryTree(TreeNode* root) {
//     // BFS, two queues
//     queue<TreeNode*> qu1, qu2;
//     unsigned int max = 0;
//     qu1.push(root);
//     queue<TreeNode*> *next = &qu2;
//     queue<TreeNode*> *current = &qu1;

//     while(!(*current).empty()) {

//       int last_not_null = 0;
//       int index = 0;
//       while(!(*current).empty()) {
//         TreeNode * node = (*current).front();
//         if(node != NULL) {
//           last_not_null = index;
//           (*next).push(node->left);
//           (*next).push(node->right);
//         }
//         index++;
//         (*current).pop();
//       }
//       if(max < last_not_null + 1) {
//         max = last_not_null+1;
//       }
//       // swap current and next
//       queue<TreeNode*> *temp = current;
//       current = next;
//       next = temp;
//       // next iteration
//     }
//     return max;
//   }

// };


// class Solution {
// public:
//   int widthOfBinaryTree(TreeNode* root) {
//     if(root == NULL) return 0;
//     // BFS, two queues
//     queue<TreeNode*> qu1, qu2;
//     int max = 0;
//     root->val = 1;
//     qu1.push(root);
//     queue<TreeNode*> *next = &qu2;
//     queue<TreeNode*> *current = &qu1;

//     while(!(*current).empty()) {
//       int t = (*current).back()->val - (*current).front()->val + 1;
//       max = (max > t) ? max : t;
//       while(!(*current).empty()) {
//         TreeNode * node = (*current).front();
//         if(node->left != NULL) {
//           node->left->val = node->val * 2;
//           (*next).push(node->left);
//         }
//         if(node->right != NULL) {
//           node->right->val = node->val * 2 + 1;
//           (*next).push(node->right);
//         }
//         (*current).pop();
//       }
//       // swap current and next
//       queue<TreeNode*> *temp = current;
//       current = next;
//       next = temp;
//       // next iteration
//     }
//     return max;
//   }

// };


// dfs's method is surely shorter and easier to debug
class Solution {
  int ans;
  map<int, int> left;
public:
  int widthOfBinaryTree(TreeNode* root) {
    ans = 0;
    dfs(root, 0, 1);
    return ans;
  }

  void dfs(TreeNode *root, int depth, int pos) {
    if(root == NULL) return;
    if(left.find(depth) == left.end()) {left[depth] = pos;} // this is based on the assumption that the left node is always first in dfs
    int t = pos - left[depth] + 1;
    ans = (ans > t) ? ans : t;
    dfs(root->left, depth+1, pos*2);
    dfs(root->right, depth+1, pos*2 + 1);
  }

};

int main() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(3);
  root->right = new TreeNode(2);
  root->left->left = new TreeNode(5);
  root->left->right = new TreeNode(3);
  root->right->left = NULL;
  root->right->right = new TreeNode(9);
  Solution test;
  cout << test.widthOfBinaryTree(root);
}
