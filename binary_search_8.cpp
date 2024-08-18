/*

给你一个 严格升序排列 的正整数数组 arr 和一个整数 k 。
请你找到这个数组里第 k 个缺失的正整数。
tips:
1 <= arr.length <= 1000
1 <= arr[i] <= 1000
1 <= k <= 1000
对于所有 1 <= i < j <= arr.length 的 i 和 j 满足 arr[i] < arr[j]
*/

/* 解题思路:
缺失指的arr是和自然数的补集,
由于是严格升序的数组，那么索引index处缺失的数miss = arr[index] - 1 - index
if miss == k, 那么ans = arr[index]
if miss < k , then shrink range
if miss > k , then shrink range
if traverse end, and left >= arr.size and miss < k , then ans = arr[size - 1] +
k;
if traverse end, and left < arr.size and miss > k , then ans = arr[right] -
miss + k - 1
*/
#include <iostream>
#include <vector>
using namespace std;

// 写的很狗屎，但还是记录一下
int findKthPositive(vector< int > &arr, int k)
{
    int size{static_cast< int >(arr.size())};
    int left{};
    int right{size - 1};
    int miss{};
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        miss = arr[mid] - 1 - mid;
        if (miss == k)
        {
            while (true)
            {
                int ans = arr[mid] - 1;
                if (mid == 0)
                {
                    return ans;
                }
                if (arr[--mid] != ans)
                {
                    return ans;
                }
            }
        }
        if (miss < k)
        {
            left = mid + 1;
        } else if (miss > k)
        {
            right = mid - 1;
        }
    }
    if (left >= size)
    {
        return arr[size - 1] + k - miss;
    }
    if (left < size)
    {
        miss = arr[left] - 1 - left;
        return arr[left] - miss + k - 1;
    }
    return -1;
}

int main()
{
    vector< int > arr = {1, 10, 21, 22, 25};
    cout << findKthPositive(arr, 12);
    return 0;
}