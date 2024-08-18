/*

给你两个整数数组 nums1 和 nums2
，请你以数组形式返回两数组的交集。返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。
*/

// 解题思路：
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector< int > intersect(vector< int > &nums1, vector< int > &nums2)
{
    unordered_map< int, int > hm1;
    unordered_map< int, int > hm2;
    for (int &num : nums1)
    {
        hm1[num]++;
    }
    for (int &num : nums2)
    {
        hm2[num]++;
    }

    vector< int > ans;
    unordered_map< int, int > *small_hm_ptr =
        hm1.size() <= hm2.size() ? &hm1 : &hm2;

    unordered_map< int, int > *large_hm_ptr =
        small_hm_ptr == &hm1 ? &hm2 : &hm1;
    for (auto &[key, value] : *small_hm_ptr)
    {
        if (large_hm_ptr->contains(key))
        {
            ans.insert(ans.end(), std::min(value, (*large_hm_ptr)[key]), key);
        }
    }

    return ans;
}

int main(int argc, char const *argv[])
{
    vector< int > nums1 = {4, 9, 5};
    vector< int > nums2 = {9, 4, 9, 8, 4};
    vector< int > ans = intersect(nums1, nums2);
    for (auto i : ans)
    {
        cout << i << ' ';
    }
    return 0;
}