#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

std::vector< int > computeLPS(const std::string &pat)
{
    std::vector< int > lps_array(pat.size(), 0);
    int lps_len = 0;  // Length of the previous longest prefix suffix
    int idx = 1;

    while (idx < pat.size())
    {
        // 检查当前字符 pat[idx] 和当前最长匹配前缀后边的字符
        // pat[lps_len] 是否相同
        if (pat[idx] == pat[lps_len])
        {
            lps_len++;
            lps_array[idx] = lps_len;
            idx++;
        } else
        {
            if (lps_len != 0)
            {
                lps_len = lps_array[lps_len - 1];  // Use the previous LPS value
            } else
            {
                lps_array[idx] = 0;
                idx++;
            }
        }
    }
    return lps_array;
}

// KMP搜索算法
void searchPatternKMP(const std::string &text, const std::string &pattern)
{
    // 计算LPS数组
    std::vector< int > lps_array = computeLPS(pattern);

    size_t textLength = text.size();
    size_t patternLength = pattern.size();

    int textIndex = 0;  // 文本串的索引

    int patternIndex = 0;  // 模式串的索引

    while (textIndex < textLength)  // 当文本索引未到结尾
    {
        // 如果当前字符匹配
        if (pattern[patternIndex] == text[textIndex])
        {
            textIndex++;     // 移动文本索引
            patternIndex++;  // 移动模式索引

            // 检查是否完成模式串的完整匹配
            if (patternIndex == patternLength)
            {
                std::cout << "Found pattern at index "
                          << textIndex - patternIndex
                          << std::endl;  // 输出匹配的开始位置

                patternIndex = 0;  // 重置patternIndex
            }
        }
        // 当前字符不匹配
        else
        {
            if (patternIndex != 0)  // 如果有部分匹配
            {
                patternIndex =
                    lps_array[patternIndex - 1];  // 使用LPS数组调整patternIndex
            } else
            {
                textIndex++;  // 如果没有部分匹配，移动文本索引
            }
        }
    }
}

int main()
{
    std::string txt = "aabbaaccaaaa";
    std::string pat = "aa";
    searchPatternKMP(txt, pat);
    return 0;
}
