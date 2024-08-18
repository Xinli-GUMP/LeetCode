#include <iostream>
#include <stdexcept>
#include <vector>

class MinHeap
{
public:
    void insert(int value);
    int pop();
    int top() const
    {
        return heap.empty() ? throw std::runtime_error("Heap is empty!")
                            : heap[0];
    }
    bool empty() const
    {
        return heap.empty();
    }
private:
    std::vector< int > heap;

    void siftUp(int index);
    void siftDown(int index);
};

void MinHeap::insert(int value)
{
    heap.push_back(value);    // 将元素放在堆的末尾
    siftUp(heap.size() - 1);  // 调整堆结构
}

int MinHeap::pop()
{
    if (heap.empty())
        throw std::runtime_error("Heap is empty!");
    int rootValue = heap[0];
    heap[0] = heap.back();  // 用最后一个元素替换根节点
    heap.pop_back();        // 移除最后一个元素
    if (!heap.empty())
    {
        siftDown(0);  // 调整堆结构
    }
    return rootValue;  // 返回原来的根节点值
}

void MinHeap::siftUp(int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (heap[index] >= heap[parentIndex])
            break;                                  // 堆的性质满足
        std::swap(heap[index], heap[parentIndex]);  // 上升调整
        index = parentIndex;
    }
}

void MinHeap::siftDown(int index)
{
    int size = heap.size();
    while (true)
    {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallestIndex = index;

        if (leftChildIndex < size && heap[leftChildIndex] < heap[smallestIndex])
        {
            smallestIndex = leftChildIndex;  // 左子节点更小
        }
        if (rightChildIndex < size &&
            heap[rightChildIndex] < heap[smallestIndex])
        {
            smallestIndex = rightChildIndex;  // 右子节点更小
        }
        if (smallestIndex == index)
            break;                                    // 堆的性质满足
        std::swap(heap[index], heap[smallestIndex]);  // 下降调整
        index = smallestIndex;
    }
}

// 测试优先队列
int main()
{
    MinHeap minHeap;
    minHeap.insert(5);
    minHeap.insert(3);
    minHeap.insert(8);
    minHeap.insert(1);

    std::cout << "最小值: " << minHeap.top() << std::endl;  // 输出1
    minHeap.pop();                                          // 删除最小值

    std::cout << "删除最小值后，新的最小值: " << minHeap.top()
              << std::endl;  // 输出3

    return 0;
}
