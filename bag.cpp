/*给你一个非负整数数组 nums 和一个整数 target 。
向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-'
，然后串联起来得到表达式 "+2-1" 。 返回可以通过上述方法构造的、运算结果等于
target 的不同 表达式 的数目。*/

#include <iostream>
#include <numeric>
#include <vector>

int findTargetSumWays(std::vector< int > &nums, int target)
{
    int ans{};
    int all_combination = 1 << nums.size();  // 2^n
    for (int i = 0; i < all_combination; i++)
    {
        std::vector< int > combination{};
        for (int j = 0; j < nums.size(); j++)
        {
            if (i & (1 << j))
            {
                // 第j位为1设为正，否则设为负
                combination.push_back(nums[j]);
            } else
            {
                combination.push_back(-nums[j]);
            }
        }
        if (std::accumulate(combination.begin(), combination.end(), 0) ==
            target)
        {
            ans++;
        }
    }

    return ans;
}

int main()
{
    std::vector< int > nums = {1, 1, 1, 1, 1};

    std::cout << findTargetSumWays(nums, 3);
    return 0;
}
