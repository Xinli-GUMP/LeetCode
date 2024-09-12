/*

给你一个二叉树的根节点 root ，按任意顺序 ，返回所有从根节点到叶子节点的路径。
叶子节点 是指没有子节点的节点。

*/

/* 解题思路:
1.深度优先搜索，前序遍历二叉树
2.如果遍历节点既没有左子树也没有右子树，则添加节点值至
*/
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right)
    {
    }
};

vector< string > binaryTreePaths(TreeNode *root)
{
    vector< string > ans_v{};
    std::stack< std::pair< TreeNode *, string > > stk;

    stk.push({root, std::to_string(root->val)});
    while (!stk.empty())
    {
        auto [node, path] = stk.top();
        stk.pop();

        if (node->left == nullptr and node->right == nullptr)
        {
            ans_v.push_back(path);
        }

        if (node->right != nullptr)
        {
            string right_path{path};
            right_path.append("->" + to_string(node->right->val));
            stk.push({node->right, right_path});
        }
        if (node->left != nullptr)
        {
            string left_path{path};
            left_path.append("->" + to_string(node->left->val));
            stk.push({node->left, left_path});
        }
    }
    return ans_v;
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(6);

    auto ans = binaryTreePaths(root);
    for (auto str : ans)
    {
        cout << str << '\n';
    }
}