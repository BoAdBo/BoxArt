#include <vector>
#include <iostream>
#include <limits.h>
using std::cout;
using std::vector;
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
  // return index
  int findmax(vector<int> nums, int low, int high) {
    int max = INT_MIN;
    int index = -1;
    for(unsigned int i = low; i <= high; ++i) {
      if(max < nums[i]) {
        max = nums[i];
        index = i;
      }
    }

    return index;
  }
  TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return constructMaximumBinaryTree(nums, 0, nums.size()-1);
  }

  TreeNode* constructMaximumBinaryTree(vector<int> &nums, int low, int high) {
    if(low <= high) {
      TreeNode *node;
      int index = findmax(nums, low, high);

      // could cause runtime error if -1 is returned
      node = new TreeNode(nums[index]);
      node->left = constructMaximumBinaryTree(nums, low, index-1);
      node->right = constructMaximumBinaryTree(nums, index+1, high);
      return node;
    }
    else {
      return NULL;
    }
  }
};
