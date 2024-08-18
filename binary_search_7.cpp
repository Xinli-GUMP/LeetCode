/*

给你两个整数数组 arr1 ， arr2 和一个整数 d ，请你返回两个数组之间的 距离值 。

「距离值」 定义为符合此距离要求的元素数目：对于元素 arr1[i] ，不存在任何元素
arr2[j] 满足 |arr1[i]-arr2[j]| <= d 。

*/

/* 解题思路:
 * 根据题意，abs(arr1[i] - arr2[j] <= d)
 * 先给arr2进行排序，二分查找，找到第一个小于arr1[i]和大于arr1[i]的元素
 * 如果这两个元素满足要求，那么所有元素都满足，ans++;
 */
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#include <algorithm>
#include <cmath>
#include <vector>

int findTheDistanceValue(std::vector< int > &arr1, std::vector< int > &arr2,
                         int d)
{
    int ans = 0;
    std::sort(arr2.begin(), arr2.end());

    for (int &num1 : arr1)
    {
        // 使用二分查找来检查 arr2 中的元素
        int left = 0;
        int right = arr2.size() - 1;
        bool is_required = true;  // 初始假设满足要求

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            // 如果找到满足条件的元素，跳出循环
            if (std::abs(num1 - arr2[mid]) <= d)
            {
                is_required = false;
                break;
            }

            if (arr2[mid] < num1)
            {
                left = mid + 1;
            } else
            {
                right = mid - 1;
            }
        }

        if (is_required)
        {
            ans++;
        }
    }

    return ans;
}

int main()
{
    vector< int > arr1 = {
        -227, 537,  -655, 993,  -526, -518, 679, -420, -53,  120,  187,
        -203, -567, -75,  464,  -472, -324, 16,  215,  -773, 862,  -563,
        -839, -906, -969, 633,  -990, 756,  -17, -346, 820,  -216, 736,
        188,  -412, 881,  -599, -181, -673, 802, 688,  553,  323,  -689,
        625,  871,  -938, -969, -207, -703, 794, 361,  111,  -884, 156,
        -223, -480, -734, -838, -53,  335,  720, -379, 855,  -971, -928,
        99,   -876, 75,   721,  -736, -913, 911};
    vector< int > arr2 = {
        -440, 599, -760, -115, -814, -611, -944, 23,   305,  -734, 524,  -429,
        406,  673, 731,  -607, 357,  -84,  -202, -325, 292,  -452, 985,  -468,
        314,  301, -503, -498, -877, 204,  915,  613,  209,  -642, -284, -123,
        239,  429, 147,  307,  69,   984,  -876, 853,  -277, 120,  -155, 102,
        -592, 457, 802,  98,   -132, 883,  356,  -857, 461,  -453, 522,  250,
        476,  991, 540,  -852, -485, -637, 999};
    cout << findTheDistanceValue(arr1, arr2, 12);
    return 0;
}