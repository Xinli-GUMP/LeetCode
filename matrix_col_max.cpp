/*
给你一个下标从 0 开始、大小为 m x n 的整数矩阵 matrix ，新建一个下标从 0
开始、名为 answer 的矩阵。使 answer 与 matrix 相等，接着将其中每个值为 -1
的元素替换为所在列的 最大 元素。 返回矩阵 answer 。 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

vector< vector< int > > modifiedMatrix(vector< vector< int > > &matrix)
{
    std::vector< vector< int > > transpose(matrix[0].size(),
                                           vector< int >(matrix.size()));

    for (int row{}; row < transpose.size(); row++)
    {
        for (int col{}; col < transpose[0].size(); col++)
        {
            transpose[row][col] = matrix[col][row];
        }
    }

    std::vector< vector< int > > ans = std::move(matrix);
    for (auto &vec : ans)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i] == -1)
            {
                vec[i] =
                    *std::max_element(transpose[i].begin(), transpose[i].end());
            }
        }
    }
    return ans;
}

int main()
{
    std::vector< vector< int > > test = {{1, 2, -1}, {4, -1, 6}, {7, 8, 9}};
    vector< vector< int > > ans = modifiedMatrix(test);
    for (const auto &vec : ans)
    {
        for (auto val : vec)
        {
            cout << val << ' ';
        }
        cout << '\n';
    }
    return 0;
}