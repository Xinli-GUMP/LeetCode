/*

给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target
，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。

*/

// 解题思路：

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int binary_search(const vector< int > &nums, int left, int right, int target)
{
    int ans = -1;
    int mid = left + (right - left) / 2;
    if (nums[mid] == target)
    {
        return mid;
    }
    if (left + 1 == right or left == right)
    {
        return nums[right] == target ? right : ans;
    }
    if (nums[mid] > target)
    {
        ans = binary_search(nums, left, mid, target);
    } else
    {
        ans = binary_search(nums, mid, right, target);
    }
    return ans;
}
int search(vector< int > &nums, int target)
{
    int left{};
    int right = nums.size() - 1;

    return binary_search(nums, left, right, target);
}

auto main() -> int
{
    vector< int > nums = {-1, 0, 3, 5, 9, 12};
    cout << search(nums, 2);
}