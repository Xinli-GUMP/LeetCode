#include <iostream>

// 定义一个可变参数模板函数
template <typename... Args>
void printValues(Args... args) {
    // 使用折叠表达式打印每个参数
    ((std::cout << args << ' '), ...);  // C++17 中的折叠表达式
    std::cout << std::endl;
}

int main() {
    printValues(1, 2.5, "Hello", 'A');  // 调用时传入多个不同类型的参数
    printValues("Only one string");      // 调用时传入一个参数
    return 0;
}
