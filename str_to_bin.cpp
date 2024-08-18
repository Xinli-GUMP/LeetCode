#include <format>  // 需要支持 C++20
#include <iostream>

std::string stringToBinary(const std::string &input)
{
    std::string binaryRepresentation;
    for (char c : input)
    {
        binaryRepresentation +=
            std::format("{:08b}", static_cast< unsigned char >(c));
    }
    return binaryRepresentation;
}

int main()
{
    std::string str = "Hello";  // 示例字符串
    std::string binaryStr = stringToBinary(str);

    // 注意 C++20 的 format 使用方法
    std::cout << "Binary representation of \"" << str << "\" is: " << binaryStr
              << std::endl;

    return 0;
}
