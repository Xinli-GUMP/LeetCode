/*

给你一个非负整数数组 nums 。如果存在一个数 x ，使得 nums 中恰好有 x 个元素
大于或者等于 x ，那么就称 nums 是一个 特殊数组 ，而 x 是该数组的 特征值 。

注意： x 不必 是 nums 的中的元素。

如果数组 nums 是一个 特殊数组 ，请返回它的特征值 x 。否则，返回 -1
。可以证明的是，如果 nums 是特殊数组，那么其特征值 x 是 唯一的 。

tips:
1 <= nums.length <= 100
0 <= nums[i] <= 1000
*/

/* 解题思路:

*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int specialArray(vector< int > &nums)
{
    std::sort(nums.begin(), nums.end());  // 先对数组进行排序
    int n = nums.size();

    // 使用二分查找可能的 x
    for (int x = 0; x <= n; ++x)
    {
        // 计算大于等于 x 的元素数量
        // 可以直接从头遍历也可以用二分查找，下面是直接遍历
        int count = std::count_if(nums.begin(), nums.end(),
                                  [x](int num)
                                  {
                                      return num >= x;
                                  });

        if (count == x)
        {
            return x;  // 找到特征值
        }
    }

    return -1;  // 如果没有找到特征值，则返回 -1
}
int main()
{
    vector< int > v = {3, 6, 7, 7, 0};
    cout << specialArray(v);
}