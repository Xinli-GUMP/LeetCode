#include <iostream>

int dow(int y, int m, int d)
{
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

int main(int argc, char const *argv[])
{
    std::cout << dow(2024, 7, 12);
    return 0;
}