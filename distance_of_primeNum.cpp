/*给你一个整数数组 nums。

返回两个（不一定不同的）质数在 nums 中 下标 的 最大距离。*/

#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

bool is_prime_num(int num)
{
    if (num < 2)
    {
        return false;
    }
    if (num == 2)
    {
        return true;
    }
    if (num % 2 == 0)
    {
        return false;
    }
    for (int i = 3; i <= std::sqrt(num); i += 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

auto maximumPrimeDifference(std::vector< int > &nums) -> int
{
    std::queue< int > prime_index_queue;
    for (int i = 0; i < nums.size(); i++)
    {
        if (is_prime_num(nums[i]))
        {
            std::cout << nums[i] << ' ';
            prime_index_queue.push(i);
        }
    }

    return prime_index_queue.back() - prime_index_queue.front();
}

int main()
{
    std::vector nums = {14, 73, 85};
    std::cout << maximumPrimeDifference(nums);
    return 0;
}
