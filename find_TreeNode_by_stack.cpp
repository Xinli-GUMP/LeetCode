#include <iostream>
#include <stack>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *findNodeIterative(TreeNode *root, int target)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    stack< TreeNode * > s;
    s.push(root);

    while (!s.empty())
    {
        TreeNode *node = s.top();
        s.pop();

        if (node->val == target)
            return node;

        // 右子树先入栈，深度优先搜索
        if (node->right != nullptr)
            s.push(node->right);

        if (node->left != nullptr)
            s.push(node->left);
    }

    return nullptr;
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    int target = 5;
    TreeNode *node = findNodeIterative(root, target);
    if (node != nullptr)
    {
        cout << "Node found with value: " << node->val << endl;
    } else
    {
        cout << "Node not found" << endl;
    }

    // 释放内存
    // (在实际代码中，需要添加释放所有动态分配内存的代码)

    return 0;
}
