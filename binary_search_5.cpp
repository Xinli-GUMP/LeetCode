/*

你总共有 n 枚硬币，并计划将它们按阶梯状排列。对于一个由 k 行组成的阶梯，其第 i
行必须正好有 i 枚硬币。阶梯的最后一行 可能 是不完整的。 给你一个数字 n
，计算并返回可形成 完整阶梯行 的总行数。

*/

// 解题思路
// 阶梯为一个首项为1，公差为1的等差数列，如果第ans项和大于n，说明ans更小，
// 反之更大，也就是说，要求前ans项的和S(ans)小于等于n，但S(ans+1)大于n。
// 等价于用二分法求右边界。
#include <iostream>
#include <vector>
using namespace std;

int arrangeCoins(int n)
{
    int ans{};
    int left{1};
    int right{n};
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        long sum_mid = mid * (1 + mid) / 2;
        if (sum_mid < n)
        {
            left = mid + 1;
        } else if (sum_mid > n)
        {
            right = mid - 1;
        } else if (sum_mid == n)
        {
            return mid;
        }
    }
    return right;
}
int main()
{
    return 0;
}