/*
541. 反转字符串 II

给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k
字符中的前 k 个字符。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
*/

/* 解题思路:
1.遍历s，当计数到达2k时，反转前k个字符
2.判断 len - 2k， 如果小于 k，则将剩下的字符也反转
3.如果 k <= len - 2k <= 2, 则转置 [idx, 3k] 范围内的字符
*/
#include <algorithm>
#include <iostream>
using namespace std;

string reverseStr(string s, int k)
{
    unsigned int len = s.length();
    int pre{};
    int nex{2 * k};
    do
    {
        if (len > k)
        {
            reverse(s.begin() + pre, s.begin() + nex - k);
        } else
        {
            reverse(s.begin(), s.end());
        }
        if (len - nex <= k and nex < len)
        {
            reverse(s.begin() + nex, s.end());
        }
        if (len - nex <= 2 * k and len - nex > k)
        {
            reverse(s.begin() + nex, s.begin() + nex + k);
        }
        pre = nex;
        nex += 2 * k;
    }
    while (nex < len);

    return s;
}

int main()
{
    string str{
        "krmyfshbspcgtesxnnljhfursyissjnsocgdhgfxubewllxzqhpasguvlrxtkgatzfybprfmmfithphckksnvjkcvnsqgsgosfxc"};
    cout << reverseStr(str, 20);
}