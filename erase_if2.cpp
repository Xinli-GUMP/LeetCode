#include <iostream>

class mystring
{
private:
    char *data;       // 动态分配的字符数组
    size_t size;      // 字符串长度
    size_t capacity;  // 容量

    void resize(size_t new_capacity)
    {
        char *new_data = new char[new_capacity];
        for (size_t i = 0; i < size; ++i)
        {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
public:
    // 构造函数
    mystring(const char *str)
    {
        size = 0;
        capacity = 16;  // 初始容量
        data = new char[capacity];

        while (str[size] != '\0')
        {
            data[size++] = str[size];
            if (size >= capacity)
            {
                resize(capacity * 2);  // 扩展容量
            }
        }
        data[size] = '\0';  // 以 '\0' 结尾
    }

    // 析构函数
    ~mystring()
    {
        delete[] data;
    }

    // 显示字符串
    void display() const
    {
        for (size_t i = 0; i < size; ++i)
        {
            std::cout << data[i];
        }
        std::cout << std::endl;
    }

    // erase_if 函数
    void erase_if(bool (*predicate)(char))
    {
        size_t write_index = 0;  // 写入索引
        for (size_t read_index = 0; read_index < size; ++read_index)
        {
            if (!predicate(data[read_index]))
            {
                data[write_index++] = data[read_index];  // 保留字符
            }
        }
        size = write_index;  // 更新大小
        data[size] = '\0';   // 重新以 '\0' 结尾
    }
};

// 自定义谓词函数
bool customPredicate(char c)
{
    return c < 'e';  // 返回 true 如果字符小于 'e'
}

int main()
{
    mystring str("example text");

    std::cout << "Original string: ";
    str.display();

    // 删除所有小于 'e' 的字符
    // str.erase_if(customPredicate);
    // customize length
    str.erase_if(
        [](char c) -> bool
        {
            int max_len = 5;
            static int count = 0;
            return (count++) > max_len;
        });

    std::cout << "After erase_if: ";
    str.display();  // 输出更新后的字符串

    return 0;
}
