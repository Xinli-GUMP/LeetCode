/*
给你一个 二进制数组
nums 。 如果一个
子数组 中 不存在 两个 相邻 元素的值 相同 的情况，我们称这样的子数组为 交替子数组
。 返回数组 nums 中交替子数组的数量。
示例 1：
输入： nums = [0,1,1,1]
输出： 5
解释：
以下子数组是交替子数组：[0] 、[1] 、[1] 、[1] 以及 [0,1] 。
*/

#include <bits/stdc++.h>
#include <vector>
using namespace std;

long long countAlternatingSubarrays(vector< int > &nums)
{
    long long ans{};
    int alternate{};
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (nums[i] != nums[i + 1])
        {
            ans = ans + alternate + 1;
            alternate++;
        } else
        {
            alternate = 0;
        }
    }
    return ans + nums.size();
}

int main(int argc, char const *argv[])
{
    vector< int > test{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1};
    cout << countAlternatingSubarrays(test);
    return 0;
}