/*

给你一个大小为 m * n 的矩阵 mat，矩阵由若干军人和平民组成，分别用 1 和 0 表示。

请你返回矩阵中战斗力最弱的 k 行的索引，按从最弱到最强排序。

如果第 i 行的军人数量少于第 j 行，或者两行军人数量相同但 i 小于
j，那么我们认为第 i 行的战斗力比第 j 行弱。

军人 总是 排在一行中的靠前位置，也就是说 1 总是出现在 0 之前。

*/

/* 解题思路:
找到每行中0的索引，即为1的个数；
创建一个vec<pair<int,int>> 存储行号和1的个数；
遍历矩阵，赋值vec；依据pair.second和pari.first对vec进行排序，返回前k个的行号。
*/
#include <algorithm>
#include <any>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
using namespace std;

vector< int > kWeakestRows(vector< vector< int > > &mat, int k)
{
    vector< pair< int, int > > line_soldiers{};
    int row_n = mat.size();
    int col_n = mat[0].size();
    for (int row_idx = 0; row_idx < row_n; ++row_idx)
    {
        int left{};
        int right{col_n - 1};
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (mat.at(row_idx).at(mid) == 0)
            {
                right = mid - 1;
            } else if (mat.at(row_idx).at(mid) == 1)
            {
                left = mid + 1;
            }
        }
        line_soldiers.push_back({row_idx, left});
    }
    // 使用 std::partial_sort 对前 k 个元素进行排序
    std::partial_sort(
        line_soldiers.begin(), line_soldiers.begin() + k, line_soldiers.end(),
        [](const std::pair< int, int > &left,
           const std::pair< int, int > &right)
        {
            return left.second < right.second ||
                   (left.second == right.second && left.first < right.first);
        });

    std::vector< int > ans_v(k);
    std::transform(line_soldiers.begin(), line_soldiers.begin() + k,
                   ans_v.begin(),
                   [](std::pair< int, int > &pair)
                   {
                       return pair.first;
                   });
    return ans_v;
};

int main()
{
    vector< vector< int > > test = {
        {1, 0, 0, 0}, {1, 1, 1, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}};
    vector< int > ans = kWeakestRows(test, 2);
    for (auto i : ans)
    {
        cout << i;
    }
    return 0;
}