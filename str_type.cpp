/*

给定两个字符串 s 和 t ，判断它们是否是同构的。

如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。

每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。

*/

/* 解题思路:
1.构建一个哈希表
2.遍历字符串, 当出现字符 a时，建立和 key = 1 的关系
3.每出现一个新的字符，key都自增 1，使得每一个字符对应的 key 都不同
4.得到两字符串对应的 key 串，对比两 key 串是否相等就行
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

bool isIsomorphic(string s, string t)
{
    unordered_map< char, int > hash_s;
    unordered_map< char, int > hash_t;
    int s_key{};
    int t_key{};
    for (char &ch : s)
    {
        hash_s.try_emplace(ch, ++s_key);
    }
    for (char &ch : t)
    {
        hash_t.try_emplace(ch, ++t_key);
    }

    string s_type;
    string t_type;

    for (char &ch : s)
    {
        s_type.push_back(hash_s[ch] + '0');
    }
    for (char &ch : t)
    {
        t_type.push_back(hash_t[ch] + '0');
    }

    return s_type == t_type;
}

int main() {}