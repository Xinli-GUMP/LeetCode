#include <iostream>

template < typename T > class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *nex;
        Node *pre;
        Node() : data(), nex(nullptr), pre(nullptr){};
        Node(const T &data) : data(data), nex(nullptr), pre(nullptr) {}
    };

    Node *head;
    Node *tail;
    std::size_t len;
public:
    LinkedList() : head(nullptr), tail(nullptr), len(0) {}
    ~LinkedList()
    {
        clear();
    }

    void clear()
    {
        Node *current = head;
        while (current)
        {
            Node *next = current->nex;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        len = 0;
    }

    void push_back(const T &value)
    {
        Node *newNode = new Node(value);
        if (!tail)
        {
            head = tail = newNode;
        } else
        {
            tail->nex = newNode;
            newNode->pre = tail;
            tail = newNode;
        }
        ++len;
    }

    // Split the list into two halves
    Node *split(Node *head)
    {
        if (!head or !head->nex)
        {
            return head;
        }
        Node *slow = head;
        Node *fast = head->nex;
        while (fast && fast->nex)
        {
            slow = slow->nex;
            fast = fast->nex->nex;
        }
        // 这里的 mid(r_head) 需要作为右半部分链表的新头，而 slow
        // 作为左半部分的尾
        Node *r_head = slow->nex;
        std::cout << "mid is: " << r_head->data << ' ';
        slow->nex = nullptr;
        return r_head;
    }

    // Merge two sorted lists
    Node *merge(Node *l1, Node *l2)
    {
        if (!l1)
            return l2;
        if (!l2)
            return l1;

        // 创建一个虚拟头节点，方便处理合并的链表
        Node dummy;
        Node *tail = &dummy;

        while (l1 && l2)
        {
            if (l1->data < l2->data)
            {
                tail->nex = l1;
                l1->pre = tail;
                l1 = l1->nex;
            } else
            {
                tail->nex = l2;
                l2->pre = tail;
                l2 = l2->nex;
            }
            tail = tail->nex;
        }
        // 处理剩余未合并部分
        if (l1)
        {
            tail->nex = l1;
            l1->pre = tail;
        } else
        {
            tail->nex = l2;
            l2->pre = tail;
        }

        // 设置新链表头节点的 pre 为 nullptr
        if (dummy.nex)
        {
            dummy.nex->pre = nullptr;
        }

        return dummy.nex;
    }

    // Sort the list using merge sort algorithm
    Node *merge_sort(Node *head)
    {
        if (!head or !head->nex)
        {
            return head;
        }
        Node *r_head = split(head);
        Node *left = merge_sort(head);
        Node *right = merge_sort(r_head);
        return merge(left, right);
    }

    void sort()
    {
        head = merge_sort(head);
        if (head)
        {
            tail = head;
            while (tail->nex)
            {
                tail = tail->nex;
            }
        }
    }

    // Output the list
    void print()
    {
        Node *current = head;
        while (current)
        {
            std::cout << current->data << " ";
            current = current->nex;
        }
        std::cout << std::endl;
    }
};

int main()
{
    LinkedList< int > list;
    list.push_back(3);
    list.push_back(1);
    list.push_back(2);
    list.push_back(4);
    list.push_back(5);

    std::cout << "Original list: ";
    list.print();

    list.sort();

    std::cout << "Sorted list: ";
    list.print();

    return 0;
}
