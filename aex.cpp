/*

给你一个字符串 columnTitle ，表示 Excel 表格中的列名称。返回
该列名称对应的列序号 。

例如：

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28
...

*/

/* 解题思路:
1.十六进制转十进制问题
2.反向遍历字符串，'A' = 65, 所以每个遍历到的字符 ch 的十进制 dec_ch = ch - 64
3.每一位的值为dec_ch * 26^i(位数)
4.答案把各个dec_ch相加就行
*/
#include <algorithm>
#include <cmath>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int integerPower(int base, int exponent)
{
    int result = 1;
    while (exponent > 0)
    {
        result *= base;
        --exponent;
    }
    return result;
}

int titleToNumber(string columnTitle)
{
    int ans = 0;
    const int base = 26;

    // Reverse the string for easier calculation
    std::string reversedTitle = columnTitle;
    std::reverse(reversedTitle.begin(), reversedTitle.end());

    // Iterate through each character in the reversed string
    for (size_t i = 0; i < reversedTitle.size(); ++i)
    {
        char ch = reversedTitle[i];

        // Check if the character is valid (A-Z)
        if (ch >= 'A' && ch <= 'Z')
        {
            // Calculate the decimal value of the character
            int dec_ch = (ch - 'A' + 1);

            // Check for overflow before multiplying
            if (INT_MAX / base < ans ||
                (INT_MAX - (ans * integerPower(base, i))) <
                    dec_ch * integerPower(base, i))
            {
                throw std::overflow_error(
                    "Column title is too long and causes an overflow.");
            }

            // Add the value to the answer
            ans += dec_ch * integerPower(base, i);
        } else
        {
            // Invalid character found
            throw std::invalid_argument("Invalid character in column title: " +
                                        std::string(1, ch));
        }
    }

    return ans;
}

// Helper function to calculate power
long integerPower(int base, size_t exp)
{
    long result = 1;
    for (size_t i = 0; i < exp; ++i)
    {
        result *= base;
    }
    return result;
}
int main() {}