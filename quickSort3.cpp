#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

// 三数取中法（median-of-three）：选择数组的第一个元素、最后一个元素和中间元素，然后取这三个元素的中值作为枢轴。这样可以减少极端情况的发生。
template < typename T, size_t LEN >
auto median_of_three(std::array< T, LEN > &arr, int left, int right) -> int
{
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid])
    {
        std::swap(arr[left], arr[mid]);
    }
    if (arr[left] > arr[right])
    {
        std::swap(arr[left], arr[right]);
    }
    if (arr[mid] > arr[right])
    {
        std::swap(arr[mid], arr[right]);
    }
    // 中间值作为枢轴
    // 将枢轴临时移到右边倒数第二个位置
    // (pivotIndex)，避免干扰分区过程
    std::swap(arr[mid], arr[right - 1]);
    return right - 1;
}

template < typename T, size_t LEN >
auto partition(std::array< T, LEN > &arr, int left, int right) -> int
{
    int pivotIndex = median_of_three(arr, left, right);
    T pivot = arr[pivotIndex];
    std::cout << "pi = " << pivot << "\t";

    // 指针交换法, 通常更高效，尤其是在处理大规模数据时。
    // new field for i+1 ~ j-1, because left < mid < right by processing
    // median_of_three(), ignore left, mid, right to avoid unnecessayy
    // comparision

    int left_boundary = left;
    int right_boundary = right - 1;

    while (true)
    {
        // while (left_boundary < right - 1 and arr[++left_boundary] < pivot) {}
        // while (right_boundary > left and arr[--right_boundary] > pivot) {}
        while (left_boundary < right_boundary and arr[++left_boundary] < pivot)
        {
        }
        while (right_boundary > left_boundary and arr[--right_boundary] > pivot)
        {
        }
        if (left_boundary < right_boundary)
        {
            std::swap(arr[left_boundary], arr[right_boundary]);
        } else
        {
            break;
        }
    }

    std::swap(arr[left_boundary], arr[right - 1]);  // Restore pivot
    return left_boundary;

    // 遍历交换法
    //     int pivotIndex = median_of_three(arr, left, right);
    //     T pivot = arr[pivotIndex];
    //     std::cout << "pi = " << pivot << "\t";
    //     int left_boundary = left;
    //     int right_boundary = right - 2;

    //     for (int index = left_boundary; index <= right_boundary; index++)
    //     {
    //         if (arr[index] < pivot)
    //         {
    //             std::swap(arr[index], arr[left_boundary]);
    //             left_boundary++;
    //         }
    //     }

    //     std::swap(arr[left_boundary], arr[right - 1]);
    //     return left_boundary;
}

template < typename T, size_t LEN >
void quickSort(std::array< T, LEN > &arr, int left = 0, int right = LEN - 1)
{
    const int small_arr_len = 0;
    if (left + small_arr_len <= right)
    {  // Use quicksort for larger subarrays,当数组的元素数量超过 30 到 50
       // 个时，快速排序的优势开始显现。
        int pivotIndex = partition(arr, left, right);

        std::cout << "sort out:  ";
        std::for_each(arr.begin(), arr.end(),
                      [](int elem)
                      {
                          std::cout << elem << '\t';
                      });
        std::cout << '\n';
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    } else
    {  // Use insertion sort for small subarrays
        for (int i = left + 1; i <= right; ++i)
        {
            T tmp = arr[i];
            int j = i - 1;
            while (j >= left and arr[j] > tmp)
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = tmp;
        }
    }
}

auto main() -> int
{
    // std::array< int, 27 > arr{34,  -999, 434, 5,   132, 23,  213, 423, 234,
    //                           2,   341,  213, 523, 634, 324, 213, 12,  221,
    //                           534, 745,  35,  0,   -1,  -13, -2,  -99, -3};

    std::array< int, 5 > arr{99, 88, 0, 77, 66};
    quickSort(arr);
    for (const auto &elem : arr)
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    return 0;
}
