/*

给定一个包含大写字母和小写字母的字符串 s ，返回 通过这些字母构造成的 最长的
回文串的长度。

在构造过程中，请注意 区分大小写 。比如 "Aa" 不能当做一个回文字符串。

*/

/* 解题思路:
1.如果一个字符出现两次，那么可以组成长度为2的回文串
2.也就是说，回文串的构成，除了中间的字符外，出现次数都为2的倍数
3.所以一个回文串的最长构成为，每个字符出现的最大偶数次之和
4.如果这个长度小于字符串长度，那么可以加一作为中心字符
*/
#include <iterator>
#include <unordered_set>
#include <vector>
using namespace std;

int longestPalindrome(string s)
{
    int len = s.length();
    if (len == 1)
    {
        return 1;
    }
    vector< int > ch_freq(256, 0);
    // statistic char frequency
    for (char ch : s)
    {
        ++ch_freq[ch];
    }
    unordered_set< char > hash_s{std::make_move_iterator(s.begin()),
                                 std::make_move_iterator(s.end())};
    // calc largeest palindrome
    int palindrome_len{};
    for (char ch : hash_s)
    {
        ch_freq[ch] % 2 == 0 ? palindrome_len += ch_freq[ch]
                             : palindrome_len += ch_freq[ch] - 1;
    }
    if (palindrome_len < len)
    {
        ++palindrome_len;
    }
    return palindrome_len;
}

int main() {}