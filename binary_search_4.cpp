/*

给你一个字符数组 letters，该数组按非递减顺序排序，以及一个字符 target。letters
里至少有两个不同的字符。

返回 letters 中大于 target 的最小的字符。如果不存在这样的字符，则返回 letters
的第一个字符。

*/

// 解题思路：
// 二分法求右边界的题目
#include <iostream>
#include <vector>
using namespace std;

char nextGreatestLetter(vector< char > &letters, char target)
{
    if (target >= letters.back())
    {
        return letters[0];
    }
    int left{};
    int right{static_cast< int >(letters.size()) - 1};
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (letters[mid] > target)
        {
            right = mid - 1;
        } else if (letters[mid] < target)
        {
            left = mid + 1;
        } else if (letters[mid] == target)
        {
            left = mid + 1;
        }
    }
    return letters.at(left);
}

int main(int argc, char const *argv[])
{
    vector< char > letters = {'e', 'e', 'e', 'e', 'e', 'e', 'n', 'n', 'n', 'n'};
    cout << nextGreatestLetter(letters, 'e');
    return 0;
}
