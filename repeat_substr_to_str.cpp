/*

给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。

*/

/* 解题思路:
1.首先，找到一个字串，如果该父串能通过字串重复构成的话，子串首字符就会重复
2.仔细一想，如果父串能够通过子串构成，那首字符一定是子串首字符
3.两个重复的首字符之间就是子串，并且字串长度与父串长度呈倍数关系
4.但是字串中可能出现多个与首字符相同的字符，这些都并非字串尾字符
5.所以记录下整个父串中所有的首字符索引，与首字符构成字串
6.再逐一判断是否能构成父串
7.判断方式是，遍历剩余的父串判断字符排列顺序是否与字串相同
8.即 s[idx] == sub[idx % sub_len]
9.这种方法过于暴力，性能不行, 优化方法参见Leedcode 495
*/
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

bool repeatedSubstringPattern(string s)
{
    uint32_t len = s.length();
    vector< int > prime_idx;
    for (int i = 1; i < len; ++i)
    {
        if (s[i] == s[0])
        {
            prime_idx.push_back(i);
        }
    }

    for (int &idx : prime_idx)
    {
        bool ans{true};
        string substr = s.substr(0, idx);
        uint32_t sub_len = substr.length();
        if (len % sub_len != 0)
        {
            continue;
        }
        for (int i = idx; i < len; ++i)
        {
            if (s[i] != s[i % sub_len])
            {
                ans = false;
                break;
            }
        }
        if (ans)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    string s{"abaabcabaabc"};
    cout << repeatedSubstringPattern(s);
}