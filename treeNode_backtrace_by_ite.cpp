#include <iostream>
#include <stack>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void printAllPaths(TreeNode *root)
{
    if (root == nullptr)
        return;

    std::stack< std::pair< TreeNode *, std::vector< int > > >
        stk;                        // 栈中的元素为节点和当前路径
    stk.push({root, {root->val}});  // 初始化，根节点入栈

    while (!stk.empty())
    {
        // 获取栈顶元素 ,结构化绑定初始化，c++17开始支持
        auto [node, path] = stk.top();
        stk.pop();

        // 判断当前节点是否是叶子节点
        if (node->left == nullptr && node->right == nullptr)
        {
            // 打印当前路径
            std::cout << "Path: ";
            for (int val : path)
            {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }

        // 如果右子树存在，先将右子树和当前路径入栈
        if (node->right != nullptr)
        {
            std::vector< int > rightPath = path;    // 复制当前路径
            rightPath.push_back(node->right->val);  // 添加右子节点值
            stk.push({node->right, rightPath});
        }

        // 如果左子树存在，后将左子树和当前路径入栈
        if (node->left != nullptr)
        {
            std::vector< int > leftPath = path;   // 复制当前路径
            leftPath.push_back(node->left->val);  // 添加左子节点值
            stk.push({node->left, leftPath});
        }
    }
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
