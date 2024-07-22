/*
给你一个下标从 0 开始的 8 x 8 网格 board ，其中 board[r][c] 表示游戏棋盘上的格子
(r, c) 。棋盘上空格用 '.' 表示，白色格子用 'W' 表示，黑色格子用 'B' 表示。
游戏中每次操作步骤为：选择一个空格子，将它变成你正在执行的颜色（要么白色，要么黑色）。但是，合法
操作必须满足：涂色后这个格子是 好线段的一个端点
（好线段可以是水平的，竖直的或者是对角线）。
好线段 指的是一个包含 三个或者更多格子（包含端点格子）的线段，线段两个端点格子为
同一种颜色 ，且中间剩余格子的颜色都为 另一种颜色 （线段上不能有任何空格子）。
给你两个整数 rMove 和 cMove 以及一个字符 color
，表示你正在执行操作的颜色（白或者黑），如果将格子 (rMove, cMove) 变成颜色 color
后，是一个 合法 操作，那么返回 true ，如果不是合法操作返回 false 。*/

#include <array>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

bool checkMove(vector< vector< char > > &board, int rMove, int cMove,
               char color)
{
    auto check = [&](int dx, int dy) -> bool
    {
        int x = rMove + dx;
        int y = cMove + dy;
        int step = 1;
        while (x >= 0 and x < 8 and y >= 0 and y < 8)
        {
            if (step == 1)
            {
                if (board[x][y] == '.' or board[x][y] == color)
                {
                    return false;
                }
            } else
            {
                if (board[x][y] == '.')
                {
                    return false;
                }
                if (board[x][y] == color)
                {
                    return true;
                }
            }
            ++step;
            x += dx;
            y += dy;
        }
        return false;
    };

    std::array< int, 8 > dx = {1, 1, 0, -1, -1, -1, 0, 1};
    std::array< int, 8 > dy = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int i = 0; i < 8; i++)
    {
        if (check(dx[i], dy[i]))
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    vector< vector< char > > board = {{'.', '.', '.', 'B', '.', '.', '.', '.'},
                                      {'.', '.', '.', 'W', '.', '.', '.', '.'},
                                      {'.', '.', '.', 'W', '.', '.', '.', '.'},
                                      {'.', '.', '.', 'W', '.', '.', '.', '.'},
                                      {'W', 'B', 'B', '.', 'W', 'W', 'W', 'B'},
                                      {'.', '.', '.', 'B', '.', '.', '.', '.'},
                                      {'.', '.', '.', 'B', '.', '.', '.', '.'},
                                      {'.', '.', '.', 'W', '.', '.', '.', '.'}};
    int rMove = 4;
    int cMove = 3;
    char color = 'B';
    cout << checkMove(board, rMove, cMove, color);
    return 0;
}