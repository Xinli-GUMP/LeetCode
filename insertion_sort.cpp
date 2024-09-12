#include <algorithm>
#include <iostream>

template < typename T = int, int len > void insertion_sort(T (&arr)[len])
{
    for (int cur = 1; cur < len; ++cur)
    {
        T key = arr[cur];
        int pre = cur - 1;
        while (pre >= 0 and key < arr[pre])
        {
            arr[pre + 1] = arr[pre];
            --pre;
        }
        arr[pre + 1] = key;
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {9, 4, 6, 12, 0, 6, 7, 3};
    insertion_sort< int >(arr);
    std::ranges::for_each(arr,
                          [](int num)
                          {
                              std::cout << num << ' ';
                          });
    return 0;
}