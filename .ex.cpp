/*

给你一座由 n x n 个街区组成的城市，每个街区都包含一座立方体建筑。给你一个下标从
0 开始的 n x n 整数矩阵 grid ，其中 grid[r][c] 表示坐落于 r 行 c
列的建筑物的高度 。

城市的天际线是从远处观察城市时，所有建筑物形成的外部轮廓。从东、南、西、北四个主要方向观测到的
天际线 可能不同。

我们被允许为 任意数量的建筑物 的高度增加 任意增量（不同建筑物的增量可能不同） 。
高度为 0 的建筑物的高度也可以增加。然而，增加的建筑物高度 不能影响
从任何主要方向观察城市得到的 天际线 。

在 不改变 从任何主要方向观测到的城市 天际线 的前提下，返回建筑物可以增加的
最大高度增量总和 。

*/

// 解题思路：
// 从南北方向看，每一列的最大高度为转置矩阵的每一行中最大元素max_t，而从东西方向看最大高度为原矩阵的每一行最大元素max，只需要使得其它元素增加值不超过min(max,
// max_t)，就能得到最大增量值。
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

int maxIncreaseKeepingSkyline(vector< vector< int > > &grid)
{
    int row = grid.size();
    int col = grid[0].size();
    vector< vector< int > > transpose{};
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            transpose[i][j] = grid[j][i];
        }
    }
    for (auto i : transpose)
    {
        for (auto j : i)
        {
            cout << j << ' ';
        }
    }
    return 0;
}

int main()
{
    vector< vector< int > > grid = {
        {3, 0, 8, 4}, {2, 4, 5, 7}, {9, 2, 6, 3}, {0, 3, 1, 0}};

    maxIncreaseKeepingSkyline(grid);

    return 0;
}
