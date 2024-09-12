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
        Node(const T &data) : data(data), nex(nullptr), pre(nullptr) {}
    };

    Node *head;
    Node *tail;
    size_t len;
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
        if (!head || !head->nex)
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
        Node *mid = slow->nex;
        slow->nex = nullptr;
        return mid;
    }

    // Merge two sorted lists
    Node *merge(Node *l1, Node *l2)
    {
        if (!l1)
            return l2;
        if (!l2)
            return l1;
        if (l1->data < l2->data)
        {
            l1->nex = merge(l1->nex, l2);
            l1->nex->pre = l1;
            l1->pre = nullptr;
            return l1;
        } else
        {
            l2->nex = merge(l1, l2->nex);
            l2->nex->pre = l2;
            l2->pre = nullptr;
            return l2;
        }
    }

    // Sort the list using merge sort algorithm
    Node *merge_sort(Node *head)
    {
        if (!head || !head->nex)
        {
            return head;
        }
        Node *mid = split(head);
        Node *left = merge_sort(head);
        Node *right = merge_sort(mid);
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
