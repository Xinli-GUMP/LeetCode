/*

给你一个下标从 0 开始的整数数组 nums 以及一个目标元素 target 。
目标下标 是一个满足 nums[i] == target 的下标 i 。
将 nums 按 非递减 顺序排序后，返回由 nums
中目标下标组成的列表。如果不存在目标下标，返回一个 空 列表。返回的列表必须按
递增 顺序排列。

tips:
1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

/* 解题思路:

*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector< int > targetIndices(vector< int > &nums, int target)
{
    std::sort(nums.begin(), nums.end());
    if (nums.front() > target or nums.back() < target)
    {
        return {};
    }
    vector< int > ans_v{};

    auto target_ite = lower_bound(nums.begin(), nums.end(), target);
    if (*target_ite == target)
    {
        ans_v.push_back(target_ite - nums.begin());
    } else
    {
        return {};
    }
    while (target_ite != nums.end() - 1)
    {
        if (*target_ite != *(++target_ite))
        {
            break;
        }
        ans_v.push_back(target_ite - nums.begin());
    }
    return ans_v;
}

int main(int argc, char const *argv[])
{
    vector< int > v = {1, 2, 2, 3, 5};
    vector< int > ans = targetIndices(v, 2);
    for (auto i : ans)
    {
        cout << i << ' ';
    }
    return 0;
}