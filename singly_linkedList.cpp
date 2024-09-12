#include <iostream>
#include <memory>
using namespace std;

class LinkedList
{
private:
    struct Node
    {
        int data;
        Node *next;

        Node(int value) : data(value), next(nullptr) {}
    };

    Node *head;  // 链表的头指针
    Node *tail;  // 链表的尾指针
public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // 在头部插入元素
    void insertAtHead(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;

        if (tail == nullptr)
        {
            tail = newNode;  // 如果链表之前为空，更新尾指针
        }
    }

    // 在尾部插入元素，复杂度 O(1)
    void insertAtTail(int value)
    {
        Node *newNode = new Node(value);
        if (tail != nullptr)
        {
            tail->next = newNode;  // 将当前尾节点的 next 指向新节点
        }
        tail = newNode;  // 更新尾指针
        if (head == nullptr)
        {
            head = newNode;  // 如果之前为空，更新头指针
        }
    }

    // 打印链表内容
    void printList()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "null" << endl;
    }

    // 析构函数，释放链表内存
    ~LinkedList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            cout << "del: " << current->data << ' ';
            delete current;
            current = nextNode;
        }
    }
};

int main()
{
    unique_ptr< LinkedList > list = std::make_unique< LinkedList >();

    list->insertAtHead(10);
    list->insertAtHead(0);
    list->insertAtTail(20);  // 使用 O(1) 插入
    list->insertAtTail(30);  // 使用 O(1) 插入
    list->printList();       // 输出: 0 -> 10 -> 20 -> 30 -> null
    return 0;
}
