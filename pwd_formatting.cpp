/*

给定一个许可密钥字符串 s，仅由字母、数字字符和破折号组成。字符串由 n
个破折号分成 n + 1 组。你也会得到一个整数 k 。
我们想要重新格式化字符串 s，使每一组包含 k 个字符，除了第一组，它可以比 k
短，但仍然必须包含至少一个字符。此外，两组之间必须插入破折号，并且应该将所有小写字母转换为大写字母。

返回 重新格式化的许可密钥 。

*/

/* 解题思路:
1.反向遍历 s，插入非破折号字符至 ans
2.每插入k个字符，插入一次破折号，注意不能在尾字符插入
3.最后再将 ans 转置
*/
#include <algorithm>
#include <cctype>
#include <iostream>
using namespace std;

string licenseKeyFormatting(string s, int k)
{
    string ans{};
    int count{};
    for (int i = s.length() - 1; i >= 0; --i)
    {
        if (s[i] != '-')
        {
            ans.push_back(static_cast< char >(std::toupper(s[i])));
            ++count;
            if (count % k == 0)
            {
                ans.push_back('-');
            }
        }
    }
    if (!ans.empty() and ans.back() == '-')
    {
        ans.pop_back();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    string s = {"---"};
    cout << licenseKeyFormatting(s, 3);
}