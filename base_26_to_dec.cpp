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
    int ans{};
    int base{26};

    reverse(columnTitle.begin(), columnTitle.end());
    for (int i = 0; i < columnTitle.length(); ++i)
    {
        int dec_ch = (columnTitle[i] - 64) * integerPower(26, i);
        ans += dec_ch;
    }
    return ans;
}
int main() {}