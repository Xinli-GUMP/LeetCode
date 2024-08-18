/*

给你一个整数数组 arr，请你检查是否存在两个整数 N 和 M，满足 N 是 M 的两倍（即，N
= 2 * M）。

更正式地，检查是否存在两个下标 i 和 j 满足：

i != j
0 <= i, j < arr.length
arr[i] == 2 * arr[j]


*/

/* 解题思路:

*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// O(logn)
bool checkIfExist(vector< int > &arr)
{
    pmr::unordered_set< int > hs_set(arr.begin(), arr.end());
    int zero_count{};
    for (int &m : arr)
    {
        if (m == 0)
        {
            zero_count++;
        }
        int n = 2 * m;
        if (zero_count == 2 or n != m and hs_set.contains(n))
        {
            return true;
        }
    }
    return false;
}
int main()
{
    std::vector< int > test = {-2, 0, 10, -19, 4, 6, -8};
    cout << checkIfExist(test);
    return 0;
}