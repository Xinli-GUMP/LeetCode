#include <cstddef>
#include <iostream>

template < typename T > class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *nex;
        Node *pre;
        Node() : data(), nex(nullptr), pre(nullptr) {}
        Node(const T &data) : data(data), nex(nullptr), pre(nullptr) {}
    };

    Node *head;       // 链表头指针
    Node *tail;       // 链表尾指针
    std::size_t len;  // 链表的长度

    // Helper function to split the list
    Node *split(Node *start, int size);
    // Helper function to merge two sorted lists
    Node *merge(Node *l1, Node *l2);
public:
    LinkedList() : head(nullptr), tail(nullptr), len(0) {}

    // Print the entire list
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

    // Append a new value to the end of the list
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

    // Entry point for the merge sort algorithm
    void merge_sort();
};

template < typename T >
typename LinkedList< T >::Node *LinkedList< T >::split(Node *start, int size)
{
    // Move 'start' forward 'size - 1' steps
    for (int i = 1; start && i < size; ++i)
    {
        start = start->nex;
    }
    if (!start)
        return nullptr;

    // Split the list and return the second part's head node
    Node *rest_head = start->nex;
    if (rest_head)
        rest_head->pre = nullptr;  // Break the link to make two separate lists
    start->nex = nullptr;
    return rest_head;
}

template < typename T >
typename LinkedList< T >::Node *LinkedList< T >::merge(Node *l1, Node *l2)
{
    // dummy define in stack, and it will be free end of the func,
    // but dummy->nex is real node which  store in head.
    Node dummy;
    Node *dummy_tail = &dummy;

    // Merge two sorted lists into one
    while (l1 && l2)
    {
        if (l1->data < l2->data)
        {
            dummy_tail->nex = l1;
            l1->pre = dummy_tail;
            l1 = l1->nex;
        } else
        {
            dummy_tail->nex = l2;
            l2->pre = dummy_tail;
            l2 = l2->nex;
        }
        dummy_tail = dummy_tail->nex;
    }

    // Link the remaining part
    dummy_tail->nex = (l1 ? l1 : l2);
    if (dummy_tail->nex)
    {
        dummy_tail->nex->pre = dummy_tail;
    }

    return dummy.nex;
}

template < typename T > void LinkedList< T >::merge_sort()
{
    if (!head || !head->nex)
    {
        return;
    }

    int list_len = len;  // Get the length of the list

    Node dummy;
    dummy.nex = head;

    // Start merging with small lists and progressively increase the size
    for (int size = 1; size < list_len; size *= 2)
    {
        Node *curr = dummy.nex;
        Node *dummy_tail = &dummy;

        while (curr)
        {
            Node *left = curr;                // Left part of the sublist
            Node *right = split(left, size);  // Right part
            curr = split(right, size);        // Next part to be processed

            Node *merged = merge(left, right);  // Merge
            dummy_tail->nex = merged;

            // Move tail pointer to the end of merged list
            while (dummy_tail->nex)
            {
                dummy_tail->nex->pre = dummy_tail;
                dummy_tail = dummy_tail->nex;
            }
        }
    }

    // Update the head pointer and reset the previous pointer of the head node
    head = dummy.nex;
    if (head)
    {
        head->pre = nullptr;
    }
}

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

    list.merge_sort();  // Sort the list

    std::cout << "Sorted list: ";
    list.print();

    return 0;
}
