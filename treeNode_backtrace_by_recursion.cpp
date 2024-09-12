#include <iostream>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void backtrack(TreeNode *node, std::vector< int > &path)
{
    if (node == nullptr)
    {
        return;  // 结束条件
    }

    // 选择：访问当前节点
    path.push_back(node->val);

    // 如果是叶子节点，打印当前路径
    if (node->left == nullptr && node->right == nullptr)
    {
        std::cout << "Path: ";
        for (int val : path)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    } else
    {
        // 递归选择左子树和右子树
        backtrack(node->left, path);
        backtrack(node->right, path);
    }

    // 回溯：恢复状态
    path.pop_back();
}

void printAllPaths(TreeNode *root)
{
    std::vector< int > path;
    backtrack(root, path);
}

int main()
{
    // 创建一个示例二叉树
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // 打印所有路径
    printAllPaths(root);

    // 释放内存（略）

    return 0;
}
