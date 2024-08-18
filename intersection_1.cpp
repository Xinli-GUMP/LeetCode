/*

给定两个数组 nums1 和 nums2 ，返回 它们的
交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。

*/

// 解题思路：
// 用哈希集合，可以变成线性复杂度？
// 遍历nums1中的元素，将nums2转为哈希集合，对比是否含有遍历到的元素
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

vector< int > intersection(vector< int > &nums1, vector< int > &nums2)
{
    set< int > ans_s;
    pmr::unordered_set< int > nums2_set(nums2.begin(), nums2.end());
    for (int &num : nums1)
    {
        if (nums2_set.contains(num))
        {
            ans_s.insert(num);
        }
    }
    vector< int > ans_v(std::make_move_iterator(ans_s.begin()),
                        std::make_move_iterator(ans_s.end()));
    return ans_v;
}