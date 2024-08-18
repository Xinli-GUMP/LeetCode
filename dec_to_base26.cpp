/*

给你一个整数 columnNumber ，返回它在 Excel 表中相对应的列名称。

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
1.'A'的ASCII值为65，减去64转换成十进制数 1, 同样 1 + 64 转换成char就是'A'
2.每一位 carry 为 columnNumber % 26 ，然后 columnNumber / 26
3.如果 carry == 0, 则说明 columnNumber为26的倍数，即 Z 的倍数
4.此时插入 Z，并且 columnNumber-- 表示进一位
*/
#include <algorithm>
#include <iostream>
using namespace std;

string convertToTitle(int columnNumber)
{
    int base{26};
    string ans{};
    int carry{};

    while (columnNumber > 0)
    {
        carry = columnNumber % base;
        if (carry == 0)
        {
            ans.push_back('Z');
            columnNumber /= base;
            --columnNumber;
        } else
        {
            ans.push_back(static_cast< char >(carry + 64));
            columnNumber /= base;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int main()
{
    int test{702};
    cout << convertToTitle(test);
}