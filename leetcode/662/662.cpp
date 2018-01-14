#include <list>
#include <vector>
#include <stdlib.h>
using std::list;
using std::vector;
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
  vector<list<TreeNode*> > levels;
public:
  int widthOfBinaryTree(TreeNode* root) {
    levels.push_back(list<TreeNode*>(1, root));

    int i = 0;
    while(!levels[i].empty()) {
      list<TreeNode*>::iterator i = levels[i].begin();
      list<TreeNode*> child;
      while(i != levels[i].end()) {
        child.push_back((*i)->left);
        child.push_back((*i)->right);
      }
      ++i;
    }
  }

  
};
