#include <iostream>
#include <ranges>
using namespace std;

int main()
{
    auto my_range = std::views::iota(0);
    for (auto i = my_range.begin(); i != my_range.begin() + 5; ++i)
    {
        cout << *i;
    }
    cout << '\n';
    auto my_range2 = std::views::iota(0, 10);
    for (int i : my_range2)
    {
        cout << i;
    }
}