#include <iostream>
#include <string>

std::u8string getCharacterAt(const std::u8string &str, size_t index)
{
    size_t byteIndex = 0;  // 当前字节索引
    size_t charCount = 0;  // 当前字符计数

    // 遍历字符串，定位到指定的字符索引
    while (byteIndex < str.length())
    {
        unsigned char c = str[byteIndex];
        size_t charSize = 0;

        // 根据第一个字节确定字符的字节长度
        if ((c & 0x80) == 0)
        {
            charSize = 1;  // 1-byte character (ASCII)
        } else if ((c & 0xE0) == 0xC0)
        {
            charSize = 2;  // 2-byte character
        } else if ((c & 0xF0) == 0xE0)
        {
            charSize = 3;  // 3-byte character
        } else if ((c & 0xF8) == 0xF0)
        {
            charSize = 4;  // 4-byte character
        }

        // 如果当前字符索引等于目标索引，返回该字符
        if (charCount == index)
        {
            return str.substr(byteIndex, charSize);  // 提取该字符
        }

        // 移动到下一个字符
        byteIndex += charSize;
        charCount++;
    }

    throw std::out_of_range("Index out of range");  // 如果索引超出范围
}

int main()
{
    std::u8string mixedStr = u8"Hello,你好世界！";  // 中英文混合字符串

    try
    {  // 打印前 7 个字符
        for (size_t i = 0; i < 7; ++i)
        {
            std::u8string charAt = getCharacterAt(mixedStr, i);
            std::cout << "第 " << i << " 个字符: "
                      << reinterpret_cast< const char * >(charAt.c_str())
                      << std::endl;
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
