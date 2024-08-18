/*


给你一个字符串 s，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中
最后一个 单词的长度。

单词 是指仅由字母组成、不包含任何空格字符的最大
子字符串
。
*/

/* 解题思路:

*/
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

int lengthOfLastWord(string s)
{
    uint64_t len{s.length()};
    uint64_t start_idx{len - 1};
    bool has_word{false};
    for (int i = len - 1; i >= 0; --i)
    {
        char cur_ch{s[i]};
        if (!has_word)
        {
            has_word = cur_ch != ' ';
        }
        cur_ch != ' ' ? --start_idx : start_idx;
        if (has_word and cur_ch == ' ' or i == 0)
        {
            return len - start_idx - 1;
        }
    }
    return len;
}
int main()
{
    return 0;
}