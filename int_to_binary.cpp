#include <algorithm>
#include <bitset>
#include <iostream>

// 将一个整数转换为二进制并返回其字符串表示
std::string intToBinary(int n)
{
    if (n == 0)
        return "0";

    std::string binary = "";
    bool isNegative = n < 0;
    if (isNegative)
    {
        n = -n;  // 取绝对值
    }

    while (n > 0)
    {
        binary += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    }

    std::reverse(binary.begin(), binary.end());

    if (isNegative)
    {
        // 将正数的二进制表示转换为负数的补码表示
        std::bitset< 32 > bits(binary);
        bits = ~bits;                // 取反
        bits = bits.to_ulong() + 1;  // 加1
        binary = bits.to_string();
    }

    return binary;
}

int main()
{
    int number = -25;
    std::string binary = intToBinary(number);
    std::cout << "The binary representation of " << number << " is " << binary
              << std::endl;
    return 0;
}
