#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <utility>

template < typename T, size_t LEN >
auto partition_midP(std::array< T, LEN > &arr, int left_index,
                    int right_index) -> int
{
    // let the middle number as a pivot
    int pivot_index = static_cast< int >((left_index + right_index) / 2);
    T pivot = arr.at(pivot_index);
    std::swap(arr.at(pivot_index),
              arr.at(right_index));  // 将枢轴移到末尾避免被交换
    int small_filed_boundary = left_index;

    for (int i = left_index; i < right_index; ++i)
    {
        if (arr.at(i) < pivot)
        {
            std::swap(arr.at(i), arr.at(small_filed_boundary));
            small_filed_boundary++;
        }
    }

    std::swap(arr.at(small_filed_boundary),
              arr.at(right_index));  // 将枢轴移回正确的位置
    return small_filed_boundary;
}

template < typename T, size_t LEN >
void quickSort_midP_Inc(std::array< T, LEN > &arr, int left_index = 0,
                        int right_index = LEN - 1)
{
    if (left_index < right_index)
    {
        int mid_index = partition_midP(arr, left_index, right_index);
        quickSort_midP_Inc(arr, left_index, mid_index - 1);
        quickSort_midP_Inc(arr, mid_index + 1, right_index);
    }
}

auto main() -> int
{
    std::array< int, 8 > arr{34, 434, 5, 132, 23, 213, 423, 234};

    quickSort_midP_Inc(arr);
    for (auto ite : arr)
    {
        std::cout << ite << '\n';
    }

    return 0;
}
