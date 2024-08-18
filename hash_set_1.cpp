/*

爱丽丝和鲍勃拥有不同总数量的糖果。给你两个数组 aliceSizes 和 bobSizes
，aliceSizes[i] 是爱丽丝拥有的第 i 盒糖果中的糖果数量，bobSizes[j]
是鲍勃拥有的第 j 盒糖果中的糖果数量。
两人想要互相交换一盒糖果，这样在交换之后，他们就可以拥有相同总数量的糖果。一个人拥有的糖果总数量是他们每盒糖果数量的总和。
返回一个整数数组 answer，其中 answer[0]
是爱丽丝必须交换的糖果盒中的糖果的数目，answer[1]
是鲍勃必须交换的糖果盒中的糖果的数目。如果存在多个答案，你可以返回其中 任何一个
。题目测试用例保证存在与输入对应的答案。

*/

// 解题思路：
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

vector< int > fairCandySwap(vector< int > &aliceSizes, vector< int > &bobSizes)
{
    vector< int > ans_v(2);
    int Alice_num = std::accumulate(aliceSizes.begin(), aliceSizes.end(), 0);
    int Bob_num = std::accumulate(bobSizes.begin(), bobSizes.end(), 0);
    int difference = (Alice_num - Bob_num) / 2;

    pmr::unordered_set< int > hs_Alice(
        std::make_move_iterator(aliceSizes.begin()),
        std::make_move_iterator(aliceSizes.end()));

    for (int &swap : bobSizes)
    {
        int need = swap + difference;
        if (hs_Alice.contains(need))
        {
            ans_v = {need, swap};
            break;
        }
    }
    return ans_v;
}