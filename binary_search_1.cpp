/*

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。
*/

// 解题思路：

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int searchInsert(vector< int > &nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            return mid;
        } else if (nums[mid] < target)
        {
            left = mid + 1;
        } else
        {
            right = mid - 1;
        }
    }
    return left;
}

int main(int argc, char const *argv[])
{
    vector< int > test = {1, 3, 5, 6};
    int target = 2;
    cout << searchInsert(test, target);
    return 0;
}