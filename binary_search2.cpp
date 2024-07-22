/*

给你一个非负整数 x ，计算并返回 x 的 算术平方根(一个数的非负平方根) 。

由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。

*/

// 解题思路：
// 在大于1的情况下，算数平方根是一定小于幂值的.

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int mySqrt(int x)
{
    int left = 0;
    int right = x;
    int mid{};
    if (x == 1)
    {
        return 1;
    }
    if (x < 1)
    {
        return 0;
    }
    while (right - left > 1)
    {
        mid = left + (right - left) / 2;
        if (mid * mid > x)
        {
            right = mid;
        } else
        {
            left = mid;
        }
    }
    return left + (right - left) / 2;
}

int main(int argc, char const *argv[])
{
    int x = 1;
    cout << mySqrt(x);
    return 0;
}