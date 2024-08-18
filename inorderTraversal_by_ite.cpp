#include <iostream>
#include <stack>

// 定义二叉树节点
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 中序遍历函数（迭代方法）
void inorderTraversal(TreeNode *root)
{
    std::stack< TreeNode * > stack;
    TreeNode *current = root;

    while (current != nullptr or !stack.empty())
    {
        // 遍历左子树，将所有左子节点压入栈中
        while (current != nullptr)
        {
            std::cout << current->val << "->in" << " ";
            stack.push(current);
            current = current->left;
        }
        // 获取栈顶元素（当前子树的最左节点）
        current = stack.top();
        std::cout << "out<<" << current->val << " ";

        // 出栈
        stack.pop();

        // 转向右子树
        current = current->right;
    }
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
     *     4
          / \
         2   6
        / \ / \
       1  3 5  7
     */
    // 进行中序遍历
    inorderTraversal(root);

    // 释放内存（实际使用中可以考虑使用智能指针自动管理内存）

    return 0;
}
