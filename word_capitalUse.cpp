/*

我们定义，在以下情况时，单词的大写用法是正确的：

全部字母都是大写，比如 "USA" 。
单词中所有字母都不是大写，比如 "leetcode" 。
如果单词不只含有一个字母，只有首字母大写， 比如 "Google" 。
给你一个字符串 word 。如果大写用法正确，返回 true ；否则，返回 false 。

*/

/* 解题思路:
1.遍历字符串
2.先检测首字符是否为大写，如果小写，则全部字符都应该为小写
3.如果大写，则分两种情况判断，如果第二个字符为小写，则后续字符都应该为小写
3.如果第二个字符为大写，则后续字符都应该为大写
4.可以使用 std::islower() std::isupper判断, 也可以使用ascii码判断
*/
#include <cctype>
#include <cstdint>
#include <iostream>
using namespace std;

bool detectCapitalUse(string word)
{
    bool detectCapitalUse(std::string word)
    {
        int len = word.length();

        // 如果长度小于等于2，都是合法的用法
        if (len < 2)
        {
            return true;
        }

        // 判断首字母
        bool isFirstUpper = std::isupper(word[0]);
        bool isSecondUpper = std::isupper(word[1]);

        // 全部小写情况
        if (!isFirstUpper)
        {
            return std::all_of(word.begin(), word.end(),
                               [](char c)
                               {
                                   return std::islower(c);
                               });
        }

        // 首字母大写且第二个字母小写
        if (!isSecondUpper)
        {
            for (int i = 2; i < len; ++i)
            {
                if (std::isupper(word[i]))
                    return false;
            }
            return true;  // 合法用法
        }

        // 首字母和第二个字母都是大写
        for (int i = 2; i < len; ++i)
        {
            if (std::islower(word[i]))
                return false;
        }

        return true;  // 合法用法
    }
}

int main()
{
    string str{"cVe"};
    cout << detectCapitalUse(str);
}