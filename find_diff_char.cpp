/*

给定两个字符串 s 和 t ，它们只包含小写字母。

字符串 t 由字符串 s 随机重排，然后在随机位置添加一个字母。

请找出在 t 中被添加的字母。

*/

/* 解题思路:
1.遍历s，记录s中字符出现的次数，因为只有ascii字符，所以用数组就行
2.遍历t，遍历到的字符出现次数减一，如果出现负数，说明这个新增字符
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

char findTheDifference(string s, string t)
{
    vector< int > char_freq_s(256, 0);
    for (char ch : s)
    {
        ++char_freq_s[ch];
    }
    for (char ch : t)
    {
        --char_freq_s[ch];
        if (char_freq_s[ch] < 0)
        {
            return ch;
        }
    }
    return ' ';
}

int main() {}