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

    const int bits =
        sizeof(dec) *
        8;  // 获取整型的位数,
            // uint有4字节，共32位，所以要完整表示uint所有取值可能需要32位
    std::string bin_str;
    bin_str.reserve(bits);  // 预分配空间

    for (int i = bits - 1; i >= 0; --i)
    {
        bin_str.push_back((dec & (1 << i)) ? '1' : '0');  // 提取当前位
    }

    // 去掉前导零
    size_t first_one = bin_str.find('1');
    return bin_str.substr(first_one);  // 返回没有前导零的二进制字符串
}

int main()
{
    int number = 10;
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
