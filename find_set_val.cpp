/*

给你两个下标从 0 开始的整数数组 nums1 和 nums2 ，它们分别含有 n 和 m
个元素。请你计算以下两个数值：

answer1：使得 nums1[i] 在 nums2 中出现的下标 i 的数量。
answer2：使得 nums2[i] 在 nums1 中出现的下标 i 的数量。
返回 [answer1, answer2]。
*/

// 解题思路：
// 先遍历num1，查找nums2中是否含有当前遍历到的元素，如果有，则ans1++。
// 再遍历num2，步骤同上

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

vector< int > findIntersectionValues(vector< int > &nums1, vector< int > &nums2)
{
    int ans1{};
    int ans2{};
    vector< int > ans_v(2);
    pmr::unordered_set< int > set1(nums1.begin(), nums1.end());
    pmr::unordered_set< int > set2(nums2.begin(), nums2.end());
    for (const int &num : nums1)
    {
        if (set2.find(num) != set2.end())
        {
            ans1++;
        }
    }
    for (const int &num : nums2)
    {
        if (set1.find(num) != set1.end())
        {
            ans2++;
        }
    }
    ans_v[0] = ans1;
    ans_v[1] = ans2;
    return ans_v;
}

int main(int argc, char const *argv[])
{
    vector< int > nums1 = {2, 3, 2};
    vector< int > nums2 = {2, 1};
    vector< int > ansv = findIntersectionValues(nums1, nums2);
    for (auto i : ansv)
    {
        cout << i << ' ';
    }
    return 0;
}
