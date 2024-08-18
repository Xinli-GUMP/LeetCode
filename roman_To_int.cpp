/*

罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1 。12 写做 XII ，即为 X + II 。
27写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做
IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值
4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个罗马数字，将其转换成整数。

*/

/* 解题思路:
1.建一个哈希表存储基本类型的罗马数字，值存储数字
2.从后往前遍历罗马数字字符，
如果前一个字符串对应的值小于当前值，那么相减，否则相加。
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int romanToInt(string s)
{
    unordered_map< char, int > roman_hsm{
        {'I', 1},   {'V', 5},   {'X', 10},   {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000},
    };
    int len = s.size();
    int ans{roman_hsm[s.back()]};
    for (int i = len - 1; i > 0; --i)
    {
        if (roman_hsm[s[i]] > roman_hsm[s[i - 1]])
        {
            ans -= roman_hsm[s[i - 1]];
        } else
        {
            ans += roman_hsm[s[i - 1]];
        }
    }
    return ans;
}

int main()
{
    return 0;
}