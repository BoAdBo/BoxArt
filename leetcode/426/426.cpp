
template <typename T>
std::insert_iterator<T> BST2LinkedList(TreeNode* root, std::insert_iterator<T> iter) {
  if (root) {
    BST2LinkedList(root->left, iter);
    iter = root->val;
    return BST2LinkedList(root->right, iter);
  }
}
