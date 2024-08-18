/*

给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。
*/

/* 解题思路:
1.先将字两个二进制字符串反转，使得每一位都对齐,并且将短的填充0至位数相等
2.遍历长的字符串，对应位相加，逢二进一
3.当前位的值为前一位 (carry + a + b ) % 2
4.下一位的进位carry为上一位 (carry + a + b) / 2
5.最后一位的carry若不为0，则额外添加一个1在结果末尾
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string addBinary(string a, string b)
{
    string ans{};
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int max_len = max(a.length(), b.length());
    a.length() == max_len ? b.resize(max_len, '0') : a.resize(max_len, '0');

    int carry{};
    for (int i = 0; i < max_len; ++i)
    {
        carry += a[i] == '1' ? 1 : 0;
        carry += b[i] == '1' ? 1 : 0;
        char cur = static_cast< char >(carry % 2) +
                   '0';  // 1~32 ascii are not to print.
        ans.push_back(cur);
        carry /= 2;
    }

    if (carry != 0)
    {
        ans.push_back('1');
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

int main(int argc, char const *argv[])
{
    string a{"1010"};
    string b{"1011"};
    cout << addBinary(a, b);
    return 0;
}