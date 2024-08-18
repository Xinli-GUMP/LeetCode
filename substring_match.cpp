/*

给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle
字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack
的一部分，则返回  -1 。
提示：
：
1 <= haystack.length, needle.length <= 104
haystack 和 needle 仅由小写英文字符组成
*/

/* 解题思路:
1.如果haystack.length < needle.length，则返回-1
2.用双指针遍历haystack
3.left记录等于needle一个字符的索引，
4.right向右扩展直到出现不等于needl的字符，如果再次遇到needle第一个字符，
则更新left的值
5.如果left往后needle.length个范围的字符和needl相同，则返回left
*/
#include <iostream>
#include <vector>
using namespace std;

// 这里采用了暴力匹配法(O(N∗M))，推荐学习KMP算法可以大幅降低时间复杂度为线性
int strStr(string haystack, string needle)
{
    int str_len{static_cast< int >(haystack.length())};
    int patt_len{static_cast< int >(needle.length())};
    for (int i = 0; i < str_len; ++i)
    {
        if (str_len - i >= patt_len)
        {
            int temp_i{i};
            for (int j = 0; j < patt_len; ++j)
            {
                if (haystack[temp_i++] != needle[j])
                {
                    break;
                }
                if (j == patt_len - 1)
                {
                    return i;
                }
            }
        }
    }
    return -1;
}

int main()
{
    string haystack = "leetcode";
    string needle = "leeto";
    cout << strStr(haystack, needle);
    return 0;
}