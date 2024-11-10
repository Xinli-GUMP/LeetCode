#include "myhead.hpp"
// arr[]: 输入的数组
// left_index, right_index: 正在排序的数组段的起始和结束索引
// 返回值: 基准值正确排序后的位置索引
template < typename T > T partition_R_Inc(T arr[], T left_index, T right_index)
{
    T pivot = arr[right_index];  // 选择数组最后一个元素作为基准
    T smaller_field_boundary =
        left_index - 1;  // smaller_field是小于基准的元素段的最右索引,
                         // 如果没有比基准元素更小的, 那么就为-1

    // 遍历除了基准外的所有元素
    for (int i = left_index; i < right_index; i++)
    {
        // 如果当前元素小于或等于pivot
        if (arr[i] <= pivot)  // 先把小于基准的元素的弄到基准元素左边
        {
            smaller_field_boundary++;  // 扩展较小元素的索引
            if (smaller_field_boundary != i)
            {
                std::swap(arr[smaller_field_boundary],
                          arr[i]);  // 把较小的元素交换到左边
            }
        }
    }

    swap(arr[smaller_field_boundary + 1],
         arr[right_index]);  // 将基准值交换到小于基准值元素段的右边第一个
    return smaller_field_boundary + 1;  // 返回新的基准值的位置索引
}

/**
 * @brief
 *
 * @tparam T
 * @tparam LEN
 * @param left_index 排序的左区间, 默认为第一个元素
 * @param right_index  排序的右区间, 默认为最后一个元素
 */
template < typename T, int LEN >
void quickSort_R_Inc(
    T (&arr)[LEN], T left_index = 0,
    T right_index = LEN -
                    1)  // 快速排序三步走, 第一步分区, 第二步排序小于基准的分区,
                        // 第三步排序大于基准的分区
{
    // 如果还有未排序的段
    if (left_index < right_index)
    {
        // 设置基准值
        T pi = partition_R_Inc(arr, left_index, right_index);

        // 对基准左侧的子数组进行递归排序
        quickSort_R_Inc(arr, left_index,
                        pi - 1);  // pi - 1是小于基准值的最右元素索引
        // 对基准右侧的子数组进行递归排序
        quickSort_R_Inc(arr, pi + 1,
                        right_index);  // pi + 1是大于基准值的最左元素索引
    }
};

template < typename T >
T partition_L_Inc(T arr[], T left_index, T right_index)  // 左基准升序分割
{
    T pivot = arr[left_index];  // 假定第一个元素为基准, 存储其值
    T larger_field_boundary =
        right_index + 1;  // 用于标定大于基准元素字段的左边界
    for (
        T i = right_index; i > left_index;
        i--)  // 反向遍历区间,除基准之外(遍历的方向一定要和排序区间扩展的方向一样,
              // 否则会出现漏网之鱼!)
    {
        if (arr[i] >= pivot)  // 把大于基准的元素放到基准左边
        {
            larger_field_boundary--;  // 基准区间左移一格
            swap(
                arr[i],
                arr[larger_field_boundary]);  // 交换当前遍历到的元素和大于基准区间的新左边界元素
        }
    };
    swap(arr[larger_field_boundary - 1],
         arr[left_index]);  // 将基准换到大区间左边一格

    return larger_field_boundary - 1;
};

/**
 * @brief
 *
 * @tparam T
 * @tparam LEN 数组长度
 * @param left_index 排序的左区间, 默认为第一个元素
 * @param right_index  排序的右区间, 默认为最后一个元素
 */
template < typename T, int LEN >
void quickSort_L_Inc(T (&arr)[LEN], T left_index = 0, T right_index = LEN - 1)
{
    if (left_index < right_index)
    {
        T pi = partition_L_Inc(arr, left_index, right_index);  // 新的基准
        quickSort_L_Inc(arr, left_index, pi - 1);
        quickSort_L_Inc(arr, pi + 1, right_index);
    }
};

template < typename T > T partition_R_Dec(T arr[], T left_index, T right_index)
{
    T pivot = arr[right_index];  // 选择最后一个元素作为基准
    T larger_field_boundary = left_index - 1;
    for (int i = left_index; i < right_index; i++)
    {
        if (arr[i] >= pivot)
        {
            larger_field_boundary++;
            swap(arr[i], arr[larger_field_boundary]);
        }
    };
    swap(arr[right_index], arr[larger_field_boundary + 1]);
    return larger_field_boundary + 1;  // 返回新的基准索引
}
/**
 * @brief
 *
 * @tparam T
 * @tparam LEN
 * @param left_index 排序的左区间, 默认为第一个元素
 * @param right_index  排序的右区间, 默认为最后一个元素
 */
template < typename T, int LEN >
void quickSort_R_Dec(T (&arr)[LEN], T left_index = 0, T right_index = LEN - 1)
{
    if (left_index < right_index)
    {
        T pi = partition_R_Dec(arr, left_index, right_index);
        quickSort_R_Dec(arr, left_index, pi - 1);
        quickSort_R_Dec(arr, pi + 1, right_index);
    }
};

template < typename T > T partition_L_Dec(T arr[], T left_index, T right_index)
{
    T pivot = arr[left_index];
    T smaller_field_boundary = right_index + 1;
    for (int i = right_index; i > left_index; i--)
    {
        if (arr[i] <= pivot)
        {
            smaller_field_boundary--;
            swap(arr[i], arr[smaller_field_boundary]);
        }
    };
    swap(arr[left_index], arr[smaller_field_boundary - 1]);
    return smaller_field_boundary - 1;
};
/**
 * @brief
 *
 * @tparam T
 * @tparam LEN
 * @param left_index 排序的左区间, 默认为第一个元素
 * @param right_index  排序的右区间, 默认为最后一个元素
 */
template < typename T, int LEN >
void quickSort_L_Dec(T (&arr)[LEN], T left_index = 0, T right_index = LEN - 1)
{
    if (left_index < right_index)
    {
        T pi = partition_L_Dec(arr, left_index, right_index);
        quickSort_L_Dec(arr, left_index, pi - 1);
        quickSort_L_Dec(arr, pi + 1, right_index);
    }
};

int main()
{
    int arr[] = {7, 999, 3, 9, 4, 2, 6, 8, 5};  // 待排序数组
    // int n = sizeof(arr) / sizeof(arr[0]); // 计算数组长度

    // quickSort_L_Inc(arr);
    quickSort_L_Dec(arr);
    print_arr(arr);
    return 0;
}
