/*

给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

进阶：

如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >=
10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

*/

/* 解题思路:
1.双指针遍历s和t
2.t_idx每次循环后移一位，s_idx 在 t[t_idx] == s[s_idx] 时后移一位
3.在边界之前查找到完整且顺序的t即为子序列
*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

bool isSubsequence(string s, string t)
{
    int s_idx{};
    int t_idx{};
    char cur_ch{};
    while (s_idx < s.length() and t_idx < t.length())
    {
        char cur_ch = s[s_idx];
        if (t[t_idx] == cur_ch)
        {
            ++s_idx;
        }
        ++t_idx;
    }
    return s_idx == s.length();
}

int main() {}