/*

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

*/

/* 解题思路:

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string longestCommonPrefix(vector< string > &strs)
{
    std::string public_prefix{};

    int max_prefix_len{static_cast< int >(strs[0].size())};
    for (int i = 1; i < strs.size(); ++i)
    {
        if (strs[i] == "")
        {
            return "";
        }
        max_prefix_len =
            std::min(max_prefix_len, static_cast< int >(strs[i].size()));
    }

    int idx{};
    while (idx < max_prefix_len)
    {
        for (int j = 1; j < strs.size(); ++j)
        {
            char pre_prefix = strs[j - 1][idx];
            char prefix = strs[j][idx];
            if (pre_prefix != prefix)
            {
                return public_prefix;
            }
        }
        public_prefix.push_back(strs[0][idx]);
        idx++;
    }

    return public_prefix;
}
int main()
{
    return 0;
}