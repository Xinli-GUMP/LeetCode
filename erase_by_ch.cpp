#include <iostream>

// 双指针删除 O(n)
void removeCharX(char *array)
{
    int read_ptr = 0;   // 读取指针
    int write_ptr = 0;  // 写入指针

    while (array[read_ptr] != '\0')
    {
        if (array[read_ptr] != 'x')
        {
            array[write_ptr] = array[read_ptr];
            write_ptr++;
        }
        read_ptr++;
    }
    array[write_ptr] = '\0';  // 以 '\0' 结尾
}

int main()
{
    char str1[] = "Hello World";  // 没有 'x'
    removeCharX(str1);
    std::cout << "Result 1: " << str1 << std::endl;  // 输出应该是 "Hello World"

    char str2[] = "example text with x characters";  // 有 'x'
    removeCharX(str2);
    std::cout << "Result 2: " << str2
              << std::endl;  // 输出应该是 "example te with  characters"

    return 0;
}
