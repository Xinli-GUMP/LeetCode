#include <cstddef>
#include <iostream>
#include <memory>
using std::cout;

template < typename T >
void merge(T *arr, T *tempArr, size_t left, size_t mid, size_t right)
{
    // unsorted elems index in left part
    size_t l_pos = left;
    // unsorted elems index in right part
    size_t r_pos = mid + 1;
    // tempArr index
    size_t pos = left;

    // if there are emels in left part and right part
    while (l_pos <= mid and r_pos <= right)
    {
        // compare two parts elems at the front, and insert the smaller into
        // tempArr
        if (arr[l_pos] <= arr[r_pos])
        {
            tempArr[pos++] = arr[l_pos++];
        } else
        {
            tempArr[pos++] = arr[r_pos++];
        }
    }

    // merge remaining elems
    // because we begin merging with single elem, so all parts are already
    // sorted. When the left part is empty, then, just merge  remaining right
    // elems after.
    while (l_pos <= mid)
    {
        tempArr[pos++] = arr[l_pos++];
    }
    while (r_pos <= right)
    {
        tempArr[pos++] = arr[r_pos++];
    }

    // cover origin arr
    while (left <= right)
    {
        arr[left] = tempArr[left];
        ++left;
    }
}

template < typename T >
void partition(T *arr, T *tempArr, size_t left, size_t right)
{
    if (left < right)
    {
        size_t mid = left + (right - left) / 2;
        // recursion divide left part
        partition(arr, tempArr, left, mid);
        // recursion divide right part
        partition(arr, tempArr, mid + 1, right);
        // merge sorted parts
        merge(arr, tempArr, left, mid, right);
    }
}

template < typename T > void merge_sort(T *arr, size_t len)
{
    // create a assistant array
    std::unique_ptr< T[] > tempArr = std::make_unique< T[] >(len);
    partition(arr, tempArr.get(), 0, len - 1);
}

int *test()
{
    std::unique_ptr< int[] > arr(new int[]{3, 5, 7, 6, 8, 9, 4});
    merge_sort(arr.get(), 7);
    for (int i = 0; i < 7; ++i)
    {
        cout << arr[i] << ' ';
    }
    return arr.get();
}

int main()
{
    int *ptr = test();
    cout << "test";
}