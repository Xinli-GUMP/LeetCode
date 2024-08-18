/*

如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个
回文串 。

字母和数字都属于字母数字字符。

给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。

*/

/* 解题思路:
1.先删除非字母数字字符，再转为小写
2.首尾双指针遍历，如果不等返回false，遍历结束返回true
*/
#include <algorithm>
#include <cctype>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;

bool isPalindrome(string s)
{
    erase_if(s,
             [](char &ch)
             {
                 return !std::isalnum(ch);
             });
    std::ranges::transform(s, s.begin(),
                           [](auto &ch)
                           {
                               return tolower(ch);
                           });

    int left{};
    int right = s.length() - 1;
    while (left < right)
    {
        if (s[left] != s[right])
        {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}
auto main() -> int {}