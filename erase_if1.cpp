#include <iostream>

// 自定义的谓词函数，判断字符是否要保留
bool customPredicate(char c, int threshold)
{
    return c > threshold;  // 返回 true 如果字符小于阈值
}

template < typename Predicate, typename... Args >
void removeChars(char *array, Predicate predicate, Args... args)
{
    int read_ptr = 0;   // 读取指针
    int write_ptr = 0;  // 写入指针

    while (array[read_ptr] != '\0')
    {
        // 使用提供的 predicate 判断字符是否应该删除
        if (!predicate(array[read_ptr], args...))
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
    // char str[] = "example text with x characters";

    // // 使用 lambda 表达式来删除所有 'x' 字符
    // removeChars(str,
    //             [](char c)
    //             {
    //                 return c == 'x';
    //             });
    // std::cout << str << std::endl;  // 输出: "example te with  characters"

    // 使用函数指针来删除小于某个阈值的字符
    char str2[] = "abcefg";  // 字符串
    int threshold = 'd';     // 自定义阈值
    removeChars(str2, customPredicate,
                threshold);          // 调用函数删除小于阈值的字符
    std::cout << str2 << std::endl;  // 应该输出: "abc"

    return 0;
}
