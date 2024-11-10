#include <algorithm>
#include <iostream>

// insertion_sort 函数模板，接受一个具有固定长度的数组，进行插入排序
template < typename T = int, int len > void insertion_sort(T (&arr)[len])
{
    for (int cur = 1; cur < len; ++cur)
    {  // 从第二个元素开始遍历数组，因为第一个元素默认是已排序的
        T key = arr[cur];  // 将当前元素（待插入元素）存储到 key
                           // 中，以防止在移动元素时丢失它
        int pre =
            cur - 1;  // 初始化 pre 索引为当前元素前一个位置，用于扫描已排序部分

        // 在已排序的子数组中从后向前扫描，寻找 key 的正确插入位置
        while (pre >= 0 and key < arr[pre])
        {
            arr[pre + 1] = arr[pre];  // 如果当前扫描的元素大于
                                      // key，就将该元素向右移动一个位置
            --pre;  // 指针前移，继续向更前的元素比较
        }

        arr[pre + 1] = key;  // 找到插入位置，将 key 放在该位置
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