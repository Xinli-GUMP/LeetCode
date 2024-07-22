#include <iostream>
#include <queue>
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
        return nullptr;

    queue< TreeNode * > q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();

        if (node->val == target)
        {
            return node;
        }

        // 注意这里是左子树先入队，和栈相反, 广度优先搜索
        if (node->left != nullptr)
            q.push(node->left);

        if (node->right != nullptr)
            q.push(node->right);
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
