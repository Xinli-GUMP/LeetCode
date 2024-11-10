#include <fcntl.h>
#include <io.h>
#include <iostream>

int main()
{
    // 设置标准输出为 UTF-8
    _setmode(_fileno(stdout), _O_U8TEXT);

    // 创建宽字符字符串
    std::wstring wideStr = L"你好，世界！";

    // 输出宽字符字符串
    std::wcout << L"宽字符字符串: " << wideStr << std::endl;

    // 输出字符数
    std::wcout << L"字符数: " << wideStr.size() << std::endl;

    // 输出宽字符串的大小（字节数）
    std::wcout << L"字符串占用的字节数: " << sizeof(wchar_t) * wideStr.length()
               << std::endl;

    return 0;
}
