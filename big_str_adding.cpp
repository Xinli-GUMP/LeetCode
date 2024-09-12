/*

给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和并同样以字符串形式返回。

你不能使用任何內建的用于处理大整数的库（比如 BigInteger），
也不能直接将输入的字符串转换为整数形式。

*/

/* 解题思路:
1.整形相加在遇到大数字时容易越界，所以用字符串模拟相加
2.先将小的字符串填充0至位对齐方便相加操作
3.双指针遍历两字符串，对齐的位的char相加
4.char -'0' 即可保留十进制运算性质
*/
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string addStrings(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    int maxLen = std::max(len1, len2);
    std::string result;

    int carry = 0;
    for (int i = 0; i < maxLen; i++)
    {
        int digit1 = (i < len1) ? num1[len1 - 1 - i] - '0' : 0;
        int digit2 = (i < len2) ? num2[len2 - 1 - i] - '0' : 0;

        int currentSum = digit1 + digit2 + carry;
        result.push_back((currentSum % 10) + '0');  // 按位添加和余数
        carry = currentSum / 10;                    // 更新进位
    }

    if (carry != 0)
    {
        result.push_back(carry + '0');  // 如果有进位，将其添加到结果中
    }

    std::reverse(result.begin(), result.end());  // 反转结果
    return result;
}

int main()
{
    string a = "456";
    string b = "77";
    cout << addStrings(a, b);
}