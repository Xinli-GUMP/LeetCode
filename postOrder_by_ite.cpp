#include <iostream>
#include <stack>
using namespace std;

// 定义二叉树的节点结构
struct TreeNode
{
    int val;          // 节点值
    TreeNode *left;   // 左子节点
    TreeNode *right;  // 右子节点

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 后序遍历的定义是：首先访问左子树，然后访问右子树，最后访问根节点；
// 迭代法后序遍历
void postOrderIterative(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    stack< TreeNode * > s;
    TreeNode *current = root;
    TreeNode *lastVisited = nullptr;

    while (!s.empty() || current != nullptr)
    {
        // 先到达最左的节点
        while (current != nullptr)
        {
            s.push(current);
            cout << "in➡️" << current->val << ' ';
            current = current->left;
        }

        // 当前节点是栈顶部元素
        current = s.top();

        // 如果右子树不存在，或者已经被访问，则可以访问当前节点
        if (current->right == nullptr || current->right == lastVisited)
        {
            cout << "out🔙" << current->val << ' ';  // 访问当前节点
            s.pop();                // 从栈中弹出当前节点
            lastVisited = current;  // 更新lastVisited
            current = nullptr;  // 将current设为NULL，进行下一个循环
        } else
        {
            // 如果右子树存在，需要先处理右子树
            current = current->right;
        }
    }
}

int main()
{
    /*
    // 创建一个示例二叉树
    //        4
    //       / \
    //      2   6
    //     / \ / \
    //    1  3 5  7
    //      / \
    //    999 888
*/
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    root->left->right->left = new TreeNode(999);  // 添加新节点 999
    root->left->right->right = new TreeNode(888);
    // 执行迭代法后序遍历
    postOrderIterative(root);

    // 释放内存（示例中没有包括内存清理的逻辑）

    return 0;
}
