/*

统计字符串中的单词个数，这里的单词指的是连续的不是空格的字符。

请注意，你可以假定字符串里不包括任何不可打印的字符。

*/

/* 解题思路:
1.用std::isalpha 来判断是否是英文字母
2.遍历字符串, 用两个变量 pre, nex 来存储前后两个字符的状态
3.当 pre is alpha and nex not is alpha 时ans++, 注意越界情况
4.需要单独处理一下 - ' 这些连字符号
*/
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int countSegments(string s)
{
    int ans{};
    s.push_back(' ');
    for (int pre = 0, nex = 1; pre < s.length() - 1; ++pre, ++nex)
    {
        if (std::isalpha(s.at(pre)) and
            (!std::isalpha(s.at(nex)) and s.at(nex) != '\'' and
             s.at(nex) != '-'))
        {
            ++ans;
        }
    }
    return ans;
}

int main()
{
    string s{"love live! mu'sic forever"};
    cout << countSegments(s);
}