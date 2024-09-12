/*

给定一个字符串 s ，找到 它的第一个不重复的字符，并返回它的索引
。如果不存在，则返回 -1 。

提示:

1 <= s.length <= 10^5
s 只包含小写字母
直接用std::count会超时
*/

/* 解题思路:
1.先遍历s构建一个哈希表记录每个char出现的次数
2.要找到第一个不重复的字符，也就意味着，第一个出现次数为1的字符
3.因为哈希表是无序的，所以再次遍历字符串，判断出现次数是否为1
4.访问数组比访问哈希更快，所以不用哈希表了
*/
#include <string>
#include <vector>
using namespace std;

int firstUniqChar(const std::string &s)
{
    // 初始化包含256个元素的数组，全部设为0
    // 256只包含Ascii字符集，如果有Unicode字符，那该方法不适用,用哈希表才行
    std::vector< int > freq(256, 0);

    for (char ch : s)
    {
        freq[ch]++;  // 统计每个字符的出现次数,这里将隐式转换成了Ascii作为索引
    }

    for (int i = 0; i < s.length(); ++i)
    {
        if (freq[s[i]] == 1)
        {
            return i;  // 找到第一个出现次数为 1 的字符
        }
    }

    return -1;  // 没有找到不重复的字符
}

int main() {}