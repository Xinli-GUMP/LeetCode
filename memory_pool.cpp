#include <iostream>
#include <memory>
#include <vector>

template < typename T > class Node
{
public:
    T data;
    Node *pre;
    Node *nex;

    Node() : data(), pre(nullptr), nex(nullptr) {}
    Node(const T &val) : data(val), pre(nullptr), nex(nullptr) {}
};

template < typename T > class NodePool
{
private:
    size_t nodeSize;      // 每次分配的节点数量
    Node< T > *pool;      // 内存池
    size_t poolCapacity;  // 当前池容量
    size_t poolUsage;     // 已使用的节点数量

    void expandPool()
    {
        size_t newSize = poolCapacity + nodeSize;  // 扩展 size
        Node< T > *newMemory = static_cast< Node< T > * >(
            ::operator new(newSize * sizeof(Node< T >)));

        // 复制已有节点到新内存
        for (size_t i = 0; i < poolUsage; ++i)
        {
            new (&newMemory[i])
                Node< T >(std::move(pool[i]));  // 使用 placement new 移动构造
        }

        // 销毁旧的节点
        for (size_t i = 0; i < poolUsage; ++i)
        {
            pool[i].~Node< T >();
        }

        // 释放旧内存
        ::operator delete(pool);

        pool = newMemory;        // 更新指针到新内存
        poolCapacity = newSize;  // 更新容量
    }
public:
    NodePool(size_t initialSize = 10, size_t nodeSize = 10)
        : nodeSize(nodeSize), poolCapacity(initialSize), poolUsage(0)
    {
        pool = static_cast< Node< T > * >(
            ::operator new(initialSize * sizeof(Node< T >)));
    }

    Node< T > *allocate()
    {
        if (poolUsage >= poolCapacity)
        {
            expandPool();
        }
        return &pool[poolUsage++];  // 分配并递增使用计数
    }

    void deallocate(Node< T > *node)
    {
        // 这里的逻辑可根据应用需求设计，例如实现一个空闲列表
        // 通过创建一个空闲链表等方式来复用节点
        node->~Node< T >();  // 调用销毁
        // 加入回收机制（非实现，需要自行实现策略）
    }

    ~NodePool()
    {
        // 销毁所有节点
        for (size_t i = 0; i < poolUsage; ++i)
        {
            pool[i].~Node< T >();
        }
        ::operator delete(pool);  // 释放内存
    }
};

template < typename T > class DoubleLinkedList
{
private:
    Node< T > *head;
    Node< T > *tail;
    NodePool< T > pool;  // 使用内存池
public:
    DoubleLinkedList(size_t poolSize = 10)
        : head(nullptr), tail(nullptr), pool(poolSize)
    {
    }

    void push_back(const T &value)
    {
        Node< T > *newNode = pool.allocate();  // 从内存池分配新节点
        newNode->data = value;
        newNode->nex = nullptr;
        newNode->pre = tail;

        if (tail)
        {
            tail->nex = newNode;
        } else
        {
            head = newNode;  // 这是第一个节点
        }
        tail = newNode;
    }

    void pop_back()
    {
        if (tail)
        {
            Node< T > *nodeToRemove = tail;

            if (tail->pre)
            {
                tail = tail->pre;
                tail->nex = nullptr;
            } else
            {
                head = tail = nullptr;  // 链表变为空
            }

            pool.deallocate(nodeToRemove);  // 将节点放回内存池
        }
    }

    // 清空链表
    void clear()
    {
        while (head)
        {
            pop_back();
        }
    }

    ~DoubleLinkedList()
    {
        clear();  // 清空链表
    }

    // 其他双链表的方法...
};

// 测试示例
int main()
{
    DoubleLinkedList< int > list;

    for (int i = 0; i < 25; ++i)
    {
        list.push_back(i);
    }

    return 0;
}
