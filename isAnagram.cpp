/*

给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。
提示:
1 <= s.length, t.length <= 5 * 104
s 和 t 仅包含小写字母
*/

/* 解题思路:
1.如果只有ASCII字符，那么只需要对俩个字符串排序，再遍历对比每一个字符是否相等就行。
2.这里把Unicode字符考虑进来，使得代码更加通用。
3.构建一个哈希表，统计每个字符出现的次数，然后对比两个哈希表是否相等。
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

bool isAnagram(string s, string t)
{
    if (s.length() != t.length())
    {
        return false;
    }

    unordered_map< char, int > hash_s;
    unordered_map< char, int > hash_t;
    for (int i = 0; i < s.length(); ++i)
    {
        hash_s[s[i]] += 1;
        hash_t[t[i]] += 1;
    }

    return hash_s == hash_t;
}

int main()
{
    string s{"啊你好啊"};
    string t{"啊好你啊"};
    cout << s << '\n' << t << '\n';
    cout << isAnagram(s, t);
}