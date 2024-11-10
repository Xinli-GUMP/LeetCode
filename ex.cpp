
#include <cstdint>
#include <iostream>
#include <memory>

auto test(const char *str) -> std::unique_ptr< uint16_t[] >
{
    auto arr = std::make_unique< uint16_t[] >(5);
    for (auto i = 0; i < 4; ++i)
    {
        arr[i] = str[i];
    }
    return arr;
}

int main()
{
    auto arr = test("ABAB");
    for (int i = 0; i < 4; ++i)
    {
        std::cout << arr[i] << std::endl;
    }
    return 0;
}