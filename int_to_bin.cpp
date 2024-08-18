#include <algorithm>
#include <iostream>
#include <stdexcept>  // 用于异常处理
#include <string>

auto int_to_bin(int dec) -> std::string
{
    if (dec < 0)
    {
        throw std::invalid_argument("Input must be a non-negative integer.");
    }

    if (dec == 0)
    {
        return "0";  // 特殊处理0的情况
    }

    std::string bin_str;
    while (dec > 0)
    {
        bin_str += (dec % 2) ? '1' : '0';  // 将余数直接转换为字符加到字符串中
        dec /= 2;
    }

    std::reverse(bin_str.begin(), bin_str.end());  // 反转字符串
    return bin_str;
}

int main()
{
    int number = -5;
    try
    {
        std::string binary_representation = int_to_bin(number);
        std::cout << "二进制表示为：" << binary_representation << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
