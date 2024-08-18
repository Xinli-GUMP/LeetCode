#include <iostream>

// 定义二叉树节点
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 中序遍历函数
void inorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return;

    // 遍历左子树
    inorderTraversal(root->left);

    // 访问根节点
    std::cout << root->val << " ";

    // 遍历右子树
    inorderTraversal(root->right);
}

int main()
{
    // 构建示例二叉树
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    /*
     *      4
          /  \
         2    6
        / \  / \
       1   3 5  7

     */

    // 进行中序遍历
    inorderTraversal(root);

    // 释放内存（实际使用中可以考虑使用智能指针自动管理内存）
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
