/*

给你一个字符串数组 words ，只返回可以使用在 美式键盘
同一行的字母打印出来的单词。键盘如下图所示。

美式键盘 中：

第一行由字符 "qwertyuiop" 组成。
第二行由字符 "asdfghjkl" 组成。
第三行由字符 "zxcvbnm" 组成。

*/

/* 解题思路:
1.构建键盘字符为 key，行号为 val 的哈希表
2.遍历 words 中的 word，判断 word 中 每个 char 的 val 是否相同
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector< string > findWords(vector< string > &words)
{
    vector< string > ans;
    vector< string > keyboard{
        "qwertyuiopQWERTYUIOP",
        "asdfghjklASDFGHJKL",
        "zxcvbnmZXCVBNM",
    };
    unordered_map< char, int > key_line;
    for (int i = 0; i < 3; ++i)
    {
        for (char &key : keyboard[i])
        {
            key_line[key] = i;
        }
    }

    for (string &str : words)
    {
        int line = key_line[str[0]];
        bool same_line{true};
        for (char &ch : str)
        {
            if (key_line[ch] != line)
            {
                same_line = false;
                break;
            }
        }
        if (same_line)
        {
            ans.push_back(str);
        }
    }

    return ans;
}

int main()
{
    vector< string > test{"Hello", "Alaska", "Dad", "Peace"};
    vector< string > ans = findWords(test);
    for (auto i : ans)
    {
        cout << i << ' ';
    }
}
