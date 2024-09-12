/*

给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine
里面的字符构成。

如果可以，返回 true ；否则返回 false 。

magazine 中的每个字符只能在 ransomNote 中使用一次。

*/

/* 解题思路:
1.先遍历 magazine 构成一个key为char，value为char的个数的哈希表
2.再遍历 ransomNote 遍历到的 char 在哈希表中的个数减一，如果出现负数，则返回
false
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

bool canConstruct(string &ransomNote, string &magazine)
{
    if (ransomNote.length() > magazine.length())
    {
        return false;
    }

    unordered_map< char, int > ch_count_map;
    for (char ch : magazine)
    {
        ch_count_map[ch] += 1;
    }
    for (char ch : ransomNote)
    {
        --ch_count_map[ch];
        if (ch_count_map[ch] < 0)
        {
            return false;
        }
    }
    return true;
}

int main() {}