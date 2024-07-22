/*

给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

完全二叉树
的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第
h 层，则该层包含 1~ 2h 个节点。

*/

// 解题思路：
// 根据完全二叉树的性质可知，左子树的深度l_depth永远为当前节点的深度减一,
// 如果左子树的深度等于右子树的深度，那说明左子树为满二叉树,拥有2^l_depth个节点；
// 如果左子树的深度不等于右子树的深度，那说明右子树为满二叉树，2^r_depth个节点；
// 先计算整棵树的深度，同时也得到了左子树的深度，再计算右子树的深度，判断左右子树深度是否相等，即可得到一半满二叉树的节点个数，然后递归求另一半二叉树。
#include <functional>
#include <iostream>
#include <climits>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr){};
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){};
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right){};
    ~TreeNode()
    {
        delete left;
        delete right;
    }
};
int countNodes(TreeNode *root)
{
    std::function< int(TreeNode *) > count_depth = [](TreeNode *root)
    {
        int depth{};
        while (root != nullptr)
        {
            root = root->left;
            ++depth;
        }
        return depth;
    };

    std::function< int(TreeNode *, int) > count_nums =
        [&](TreeNode *root, int l_depth)
    {
        if (root == nullptr)
        {
            return 0;
        }
        int r_depth = count_depth(root->right);
        if (l_depth == r_depth)
        {
            return (1 >> l_depth) + count_nums(root->right, r_depth - 1);
        }
        return (1 >> r_depth) + count_nums(root->left, l_depth - 1);
    };

    int depth = count_depth(root);
    int ans = count_nums(root, depth - 1);
    return ans;
}

int main(int argc, char const *argv[])
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    cout << countNodes(root);
    return 0;
}