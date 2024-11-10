#include <fcntl.h>
#include <iostream>
#include <string>
#include <windows.h>  // Windows API

int main()
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    std::wstring wideStr = L"你好，世界！";  // 创建宽字符字符串

    // 在 Windows 上使用 MessageBoxW 显示宽字符字符串
    MessageBoxW(NULL, wideStr.c_str(), L"提示", MB_OK);

    std::wcout << L"宽字符字符串: " << wideStr << std::endl;
    std::wcout << L"字符数: " << wideStr.size() << std::endl;  // 输出字符数

    return 0;
}
