// 定义二叉树节点
#include <iostream>
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
// 计算树的高度
int computeHeight(TreeNode *node)
{
    int height = 0;
    while (node != nullptr)
    {
        height++;
        node = node->left;
    }
    return height;
}

// 计算完全二叉树的节点数
int countNodes(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int totalHeight = computeHeight(root);
    int nodeCount = 0;

    while (root != nullptr)
    {
        int rightHeight = computeHeight(root->right);
        int leftHeight = totalHeight - 1;

        if (leftHeight == rightHeight)
        {
            // 左子树是满的
            nodeCount += (1 << leftHeight);
            root = root->right;
        } else
        {
            // 右子树是满的
            nodeCount += (1 << rightHeight);
            root = root->left;
        }

        totalHeight--;
    }

    return nodeCount;
}
int main()
{
    // 构建一个示例完全二叉树
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    std::cout << "节点总数: " << countNodes(root) << std::endl;

    // 释放内存（实际使用中可以考虑使用智能指针自动管理内存）
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}