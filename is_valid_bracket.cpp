/*

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。

*/

/* 解题思路:
1.如果 s 长度为奇数，则必定为false.
2.构建一个字典，左括号键对应右括号值
3.使用栈，遍历字符串，如果为左括号，入栈
4.否则就是右括号，判断栈顶元素是否为对应的左括号，
5.对应则出栈，不对应就返回false
6.最后检查栈是否为空，为空则说明所有括号闭合
*/
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

bool isValid(string s)
{
    if (s.length() % 2 != 0)
    {
        return false;
    }

    unordered_map< char, char > bracket_m{{'(', ')'}, {'[', ']'}, {'{', '}'}};
    std::stack< char > stk{};
    for (char &ch : s)
    {
        // if is opening bracket
        if (bracket_m.contains(ch))
        {
            stk.push(ch);
        } else  // closed bracket
        {
            char top_elem{stk.empty() ? '#' : stk.top()};
            if (bracket_m[top_elem] == ch)
            {
                stk.pop();
            } else
            {
                return false;
            }
        }
    }
    return stk.empty();
}
int main()
{
    return 0;
}