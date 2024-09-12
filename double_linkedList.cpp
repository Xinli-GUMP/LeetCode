#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <utility>
using std::cout;

template < typename T > class LinkedList
{
    // std::ptrdiff_t常用于表示迭代器或指针之间的差值
    using difference_type = std::ptrdiff_t;
    // using Val = T;
    using Ptr = T *;
    using Ref = T &;
    using iterator_category = std::bidirectional_iterator_tag;
public:
    struct Node
    {
        T data;
        Node *pre;
        Node *nex;
        Node() : data(), pre(nullptr), nex(nullptr){};
        Node(const T &val) : data(val), pre(nullptr), nex(nullptr){};
    };

    class Iterator
    {
        friend LinkedList;
    private:
        Node *current;
    public:
        Iterator() : current(nullptr){};
        Iterator(Node *node) : current(node){};

        Ref operator*() const
        {
            return current->data;
        }

        Ptr operator->() const
        {
            return &(current->data);
        }

        Iterator &operator++()
        {
            if (current != nullptr)
            {
                current = current->nex;
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator &operator--()
        {
            if (current != nullptr)
            {
                current = current->pre;
            }
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator &other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }

        Iterator operator+(difference_type n)
        {
            Iterator temp = *this;
            while (n-- > 0 and temp.current != nullptr)
            {
                ++temp;
            }
            return temp;
        }

        Iterator &operator+=(difference_type n)
        {
            while (n-- > 0 and current != nullptr)
            {
                ++(*this);
            }
            return *this;
        }

        Iterator operator-(difference_type n)
        {
            Iterator temp = *this;
            while (n-- > 0 and temp.current != nullptr)
            {
                --temp;
            }
            return temp;
        }

        Iterator &operator-=(difference_type n)
        {
            while (n-- > 0 and current != nullptr)
            {
                --(*this);
            }
            return *this;
        }

        difference_type distance(const Iterator &other) const
        {
            difference_type dist{};
            Iterator temp = *this;
            while (temp.current != nullptr and temp != other)
            {
                ++dist;
                ++temp;
            }
            if (temp == other)
            {
                return dist;
            }
            // other 不在当前节点右方，重置距离，反向寻找
            dist = 0;
            temp = *this;
            while (temp.current != nullptr and temp != other)
            {
                --dist;
                --temp;
            }
            if (temp == other)
            {
                return dist;
            }
            // 未寻找到 other 节点
            throw "Two Iterators do not belong to the same LinkedList";
        }
    };

    LinkedList() : len(), head(nullptr), tail(nullptr){};

    LinkedList(Iterator begin, Iterator end)
        : len(), head(nullptr), tail(nullptr)
    {
        for (auto ite = begin; ite != end; ++ite)
        {
            tail_insert(*ite);
        }
    };

    LinkedList(const LinkedList &other)
        : len(other.len), head(nullptr), tail(nullptr)
    {
        if (other.head == nullptr)
        {
            return;
        }

        head = new Node(other.head->data);
        Node *current_node = head;
        Node *other_current_nex = other.head->nex;
        while (other_current_nex != nullptr)
        {
            current_node->nex = new Node(other_current_nex->data);
            current_node->nex->pre = current_node;
            current_node = current_node->nex;
            other_current_nex = other_current_nex->nex;
        }
        tail = current_node;
    }

    LinkedList(LinkedList &&other) noexcept
        : len(other.len), head(other.head), tail(other.tail)
    {
        other.len = 0;
        other.head = nullptr;
        other.tail = nullptr;
    }

    ~LinkedList()
    {
        Node *current = head;
        // cout << '\n';
        while (current != nullptr)
        {
            Node *next_node = current->nex;
            // cout << "del: " << current->data << ' ';
            delete current;
            current = next_node;
        }
    }

    size_t size()
    {
        return len;
    }

    /**
     * @brief      return true if empty
     *
     * @return     true or false
     */
    bool empty()
    {
        if (head == nullptr and len == 0)
        {
            return true;
        }
        if (head == nullptr and len != 0 or head != nullptr and len == 0)
        {
            throw "LinkedList structure get broken!";
        }
        return false;
    }

    Iterator begin()
    {
        return Iterator(head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    Iterator rbegin()
    {
        return Iterator(tail);
    }

    Iterator rend()
    {
        return Iterator(nullptr);
    }

    /**
     * @brief      get the mid node between begin and end
     *
     * @param[in]  begin  Iterator
     * @param[in]  end    Iterator
     *
     * @return     mid node's iterator
     */
    Iterator mid(Iterator begin, Iterator end) const
    {
        if (begin == end or (begin + 1) == end)
        {
            return begin;
        }
        Iterator slow = begin;
        Iterator faster = begin + 1;
        while (faster != end and (faster + 1) != end)
        {
            slow += 1;
            faster += 2;
        }
        return slow;
    }

    /**
     * @brief      create a new node at tail
     *
     * @param[in]  value  The value
     */
    void tail_insert(const T &value)
    {
        Node *new_node = new Node(value);
        if (tail != nullptr)
        {
            tail->nex = new_node;
            new_node->pre = tail;
            tail = new_node;
        } else
        {
            head = tail = new_node;
        }
        ++len;
    }

    void head_insert(const T &value)
    {
        Node *new_node = new Node(value);
        if (head != nullptr)
        {
            head->pre = new_node;
            new_node->nex = head;
            head = new_node;
        } else
        {
            head = tail = new_node;
        }
        ++len;
    }

    /**
     * @brief      insert in front of the node
     *
     * @param[in]  value
     * @param      node
     */
    void insert_before(const T &value, Iterator pos)
    {
        Node *node = pos.current;
        if (node == head)
        {
            head_insert(value);
            return;
        }
        Node *new_node = new Node(value);
        new_node->pre = node->pre;
        new_node->nex = node;
        if (node->pre != nullptr)
        {
            node->pre->nex = new_node;
        }
        // 这里注意顺序，需要先修改上一个节点的next，再修改节点的pre
        node->pre = new_node;
        ++len;
    }

    /**
     * @brief      insert behind the node
     *
     * @param[in]  value  new node data
     * @param      node   target node
     */
    void insert_after(const T &value, Iterator pos)
    {
        Node *node = pos.current;
        if (node == tail)
        {
            tail_insert(value);
        } else
        {
            Node *new_node = new Node(value);
            new_node->nex = node->nex;
            new_node->pre = node;
            if (node->nex != nullptr)
            {
                node->nex->pre = new_node;
            }
            node->nex = new_node;
            ++len;
        }
    }

    /**
     * @brief      insert in this index
     *
     * @param[in]  value     data
     * @param[in]  position  index
     */
    void insert_at(const T &value, size_t position)
    {
        if (position <= 1)
        {
            head_insert(value);
            return;
        }
        if (position > len)
        {
            tail_insert(value);
            return;
        }
        Node *new_node = new Node(value);
        Node *current = head;
        size_t cur_pos{1};
        while (cur_pos != position)
        {
            ++cur_pos;
            current = current->nex;
        }
        new_node->pre = current->pre;
        new_node->nex = current;
        if (current->pre != nullptr)
        {
            current->pre->nex = new_node;
        }
        current->pre = new_node;
        ++len;
    }

    /**
     * @brief      move this node in front of position
     *
     * @param      moved     moved node
     * @param      position  target node
     */
    void move_before(Iterator moved, Iterator position)
    {
        Node *moved_node = moved.current;
        Node *position_node = position.current;
        if (moved_node == position_node or position_node == nullptr)
        {
            return;
        }
        // unlink
        if (moved_node->pre != nullptr)
        {
            moved_node->pre->nex = moved_node->nex;
        }
        //  moved->pre == nullptr, then moved is head
        else
        {
            head = moved_node->nex;
        }
        if (moved_node->nex != nullptr)
        {
            moved_node->nex->pre = moved_node->pre;
        } else
        {
            tail = moved_node->pre;
        }
        moved_node->pre = position_node->pre;
        moved_node->nex = position_node;
        position_node->pre = moved_node;
        if (position_node == head)
        {
            head = moved_node;
        }
        // If position not is head, then there is a node before.
        else if (moved_node->pre != nullptr)
        {
            moved_node->pre->nex = moved_node;
        }
    }

    void move_after(Iterator moved, Iterator position)
    {
        Node *moved_node = moved.current;
        Node *position_node = position.current;

        if (moved_node == position_node or position_node == nullptr)
        {
            return;
        }
        // un-link moved node
        if (moved_node->pre != nullptr)
        {
            moved_node->pre->nex = moved_node->nex;
        }
        // moved->pre == nullptr, then moved is head
        else
        {
            head = moved_node->nex;
        }
        if (moved_node->nex != nullptr)
        {
            moved_node->nex->pre = moved_node->pre;
        } else
        {
            tail = moved_node->pre;
        }

        // re-link moved node
        moved_node->pre = position_node;
        moved_node->nex = position_node->nex;
        position_node->nex = moved_node;
        if (position_node == tail)
        {
            tail = moved_node;
        }
        // If position is not tail, then there is a node after position
        else
        {
            moved_node->nex->pre = moved_node;
        }
    }

    void pop_front()
    {
        Node *temp = head;
        head = temp->nex;
        head->pre = nullptr;
        delete temp;
        --len;
    }

    void pop_back()
    {
        Node *temp = tail;
        tail = temp->pre;
        tail->nex = nullptr;
        delete temp;
        --len;
    }

    void erase_node(Iterator erased)
    {
        Node *node = erased.current;
        if (node == head)
        {
            pop_front();
            return;
        }
        if (node == tail)
        {
            pop_back();
            return;
        }
        if (node->pre != nullptr)
        {
            node->pre->nex = node->nex;
        }
        if (node->nex != nullptr)
        {
            node->nex->pre = node->pre;
        }
        delete node;
        --len;
    }

    /**
     * @brief      erase node which index eq position
     *
     * @param[in]  position
     */
    void erase_at(size_t position)
    {
        if (position <= 1)
        {
            pop_front();
            return;
        }
        if (position >= len)
        {
            pop_back();
            return;
        }
        Node *current_node = head;
        for (size_t i = 1; i < position; ++i)
        {
            current_node = current_node->nex;
        }
        if (current_node->pre != nullptr)
        {
            current_node->pre->nex = current_node->nex;
        }
        if (current_node->nex != nullptr)
        {
            current_node->nex->pre = current_node->pre;
        }
        delete current_node;
        --len;
    }

    /**
     * @brief      erase all nodes which node->data eq data
     *
     * @param[in]  data
     */
    void erase_if(T data)
    {
        Node *current_node = head;
        while (current_node != nullptr)
        {
            if (current_node->data == data)
            {
                erase_node(Iterator(current_node));
            }
        }
    }

    /**
     * @brief      Finds first node which data eq value.
     *
     * @param[in]  value  The value
     *
     * @return     Iterator
     */
    Iterator find_node_by_data(const T value)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return Iterator(current);
            }
            current = current->nex;
        }
        return Iterator(nullptr);
    }

    /**
     * @brief      Finds a node by position.
     *
     * @param[in]  position  The index
     *
     * @return     { Iterator which index(begin at 1) eq positon }
     */
    Iterator find_node_by_pos(const size_t position)
    {
        if (position < 1 or position > len)
        {
            return Iterator(nullptr);
        }
        Node *current_node = head;
        for (size_t i = 1; i < position; ++i)
        {
            current_node = current_node->nex;
        }
        return Iterator(current_node);
    }

    void reverse()
    {
        if (len <= 1)
        {
            return;
        }
        tail = head;
        Node *current_pre = nullptr;
        Node *current_node = head;
        Node *current_nex = nullptr;
        while (current_node != nullptr)
        {
            current_nex = current_node->nex;
            current_node->pre = current_nex;
            current_node->nex = current_pre;
            current_pre = current_node;
            current_node = current_nex;
        }
        head = current_pre;
        head->pre = nullptr;
        tail->nex = nullptr;
    }

    bool is_adjoin(const Iterator iterator1, const Iterator iterator2)
    {
        return iterator1.current->pre == iterator2.current or
               iterator1.current->nex == iterator2.current;
    }

    /**
     * @brief      swap two nodes' data but don't change relative position
     *
     * @param      node1  The node 1
     * @param      node2  The node 2
     */
    void swap_data(Iterator iterator1, Iterator iterator2)
    {
        Node *node1 = iterator1.current;
        Node *node2 = iterator2.current;
        if (node1 == node2 or !node1 or !node2)
        {
            return;
        }
        std::swap(node1->data, node2->data);
    }

    /**
     * @brief      swap two nodes' relative positon, of course, include data
     *
     * @param      iterator1
     * @param      iterator2
     */
    void swap_node(Iterator iterator1, Iterator iterator2)
    {
        Node *node1 = iterator1.current;
        Node *node2 = iterator2.current;
        if (node1 == node2 or len <= 1 or !node1 or !node2)
        {
            return;
        }

        // make sure node1 is the left node
        if (is_adjoin(node1, node2) and node1->nex != node2)
        {
            std::swap(node1, node2);
        }
        Node *pre1 = node1->pre;
        Node *nex1 = node1->nex;
        Node *pre2 = node2->pre;
        Node *nex2 = node2->nex;
        if (pre1 != nullptr)
        {
            pre1->nex = node2;
        }
        if (nex2 != nullptr)
        {
            nex2->pre = node1;
        }
        if (is_adjoin(node1, node2))
        {
            node1->pre = node2;
            node1->nex = nex2;
            node2->pre = pre1;
            node2->nex = node1;
        } else
        {
            node1->pre = pre2;
            node1->nex = nex2;
            node2->pre = pre1;
            node2->nex = nex1;
            if (nex1 != nullptr)
            {
                nex1->pre = node2;
            }
            if (pre2 != nullptr)
            {
                pre2->nex = node1;
            }
        }

        if (node1 == head)
        {
            head = node2;
        } else if (node2 == head)
        {
            head = node1;
        }
        if (node1 == tail)
        {
            tail = node2;
        } else if (node2 == tail)
        {
            tail = node1;
        }
    }

    /**
     * @brief    O(N^2) Insertion sort is suitable for small amounts of data.
     */
    void insertion_sort()
    {
        if (len == 1)
        {
            return;
        }

        // 目标节点的下一个节点值 > 当前排序值
        auto find_insert_pos = [](Node *start, T &value) -> Node *
        {
            Node *cur_node = start;
            while (cur_node->nex != nullptr and cur_node->nex->data < value)
            {
                cur_node = cur_node->nex;
            };
            return cur_node;
        };

        // 哨兵节点创建在栈上省的释放
        Node dummy_node;
        dummy_node.nex = head;
        // 确保能够在头节点之前插入节点
        head->pre = &dummy_node;

        Node *sorted_end = head;
        Node *cur_node = head->nex;
        while (cur_node != nullptr)
        {
            Node *nex_node = cur_node->nex;
            if (cur_node->data >= sorted_end->data)
            {
                sorted_end = cur_node;
            } else
            {
                Node *insert_pos = find_insert_pos(&dummy_node, cur_node->data);
                // unlink cur_node
                sorted_end->nex = cur_node->nex;
                if (cur_node->nex != nullptr)
                {
                    cur_node->nex->pre = sorted_end;
                }
                // relink cur_node for insertion (after position)
                cur_node->pre = insert_pos;
                cur_node->nex = insert_pos->nex;
                if (insert_pos->nex != nullptr)
                {
                    insert_pos->nex->pre = cur_node;
                }
                insert_pos->nex = cur_node;
            }
            cur_node = nex_node;
        }

        head = dummy_node.nex;
        head->pre = nullptr;
        tail = sorted_end;
    }

    /**
     * @brief   O(N*LogN)  Merge sort is suitable for a large amounts of data.
     */
    void merge_sort()
    {
        // Define split function
        auto split = [](Node *start, size_t size) -> Node *
        {
            // Move 'start' forward 'size - 1' steps
            for (size_t i = 1; start != nullptr and i < size; ++i)
            {
                start = start->nex;
            }
            if (start == nullptr)
            {
                return nullptr;
            }

            // split list and return the second part's head node
            Node *r_head = start->nex;
            // Break the link to make two separate lists
            if (r_head)
            {
                r_head->pre = nullptr;
            }
            start->nex = nullptr;

            return r_head;
        };

        // Define merge function
        auto merge = [](Node *list1, Node *list2) -> Node *
        {
            // dummy define in stack, and it will be free end of the func,
            // but dummy->nex is real node which  store in heap.
            Node dummy;
            Node *dummy_tail = &dummy;

            // Merge two lists into one
            while (list1 and list2)
            {
                if (list1->data < list2->data)
                {
                    dummy_tail->nex = list1;
                    list1->pre = dummy_tail;
                    list1 = list1->nex;
                } else
                {
                    dummy_tail->nex = list2;
                    list2->pre = dummy_tail;
                    list2 = list2->nex;
                }
                dummy_tail = dummy_tail->nex;
            }

            // Link the remaining part, it's already sorted
            dummy_tail->nex = (list1 ? list1 : list2);
            if (dummy_tail->nex)
            {
                dummy_tail->nex->pre = dummy_tail;
            }

            return dummy.nex;
        };

        if (head == nullptr or head->nex == nullptr)
        {
            return;
        }

        int list_len = this->len;
        // create  sentinel Node
        Node dummy;
        dummy.nex = head;

        // Start merging with small lists and progressively increase the size
        for (size_t size = 1; size < list_len; size *= 2)
        {
            Node *cur = dummy.nex;
            Node *dummy_tail = &dummy;

            while (cur)
            {
                // Left head of the sublist
                Node *left = cur;

                // Right head of the other sublist
                Node *right = split(left, size);

                // pre-store next part head of sublist
                cur = split(right, size);

                // Merge left part sublist and right part
                Node *merged = merge(left, right);

                // link dummy node to compose new sorted list
                dummy_tail->nex = merged;

                // update muddy_tail to the end of sorted list
                while (dummy_tail->nex)
                {
                    dummy_tail->nex->pre = dummy_tail;
                    dummy_tail = dummy_tail->nex;
                }
            }
        }

        // Update the head pointer and reset the previous pointer of the
        // head node
        head = dummy.nex;
        if (head)
        {
            head->pre = nullptr;
        }
    };

    /**
     * @brief      Delete all nodes and reset list't len to 0.
     */
    void clear()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *next_node = current->nex;
            // cout << "del: " << current->data << ' ';
            delete current;
            current = next_node;
        }
        len = 0;
    }

    void print_list() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->data << ' ';
            current = current->nex;
        }
    }
private:
    size_t len;
    Node *head;
    Node *tail;
};

void test()
{
    std::unique_ptr< LinkedList< size_t > > list =
        std::make_unique< LinkedList< size_t > >();
    //  list->head_insert(2);
    // list->head_insert(1);
    // list->tail_insert(9);
    // list->tail_insert(10);
    // list->insert(3, 3);
    // list->insert(4, 4);

    // auto *target_node = list->find_node_by_data(9);
    // list->insert(6, target_node);
    // list->insert(7, target_node);

    list->insert_at(1, 1);
    list->insert_at(21, 2);
    for (auto i = 2; i < 21; i++)
    {
        list->insert_at(i, i);
    }

    cout << '\n';
    // list->pop_front();
    // list->pop_back();
    // auto *target_node = list->find_node_by_data(10);
    // list->erase_node(target_node);
    // list->erase_node(target_node->pre);
    // list->erase_node(target_node->nex);

    // for (size_t i = 0; i < 10; ++i)
    // {
    //     list->erase_at(10);
    // }

    auto target_node2 = list->find_node_by_pos(13);
    list->erase_node(target_node2);
    cout << *target_node2 << '\n';
    list->print_list();

    list->clear();
}

void test2()
{
    LinkedList< size_t > *list = new LinkedList< size_t >;
    list->tail_insert(22);
    list->tail_insert(11);
    list->head_insert(33);
    // LinkedList< size_t > *list2 = new LinkedList(*list);
    LinkedList< size_t > *list3 = new LinkedList(std::move(*list));
    delete list;
    delete list3;
}

void test3()
{
    LinkedList< size_t > list;
    for (size_t i = 0; i < 100; ++i)
    {
        list.tail_insert(i);
    }
    list.reverse();
    list.print_list();
}

void test4()
{
    LinkedList< size_t > *list = new LinkedList< size_t >;
    for (size_t i = 1; i < 6; ++i)
    {
        list->tail_insert(i);
    }
    auto node1 = list->find_node_by_pos(1);
    auto node2 = list->find_node_by_pos(2);
    auto node3 = list->find_node_by_pos(3);
    auto node5 = list->find_node_by_pos(5);
    list->swap_node(node1, node5);
    list->swap_node(node2, node3);
    list->swap_node(node3, list->find_node_by_pos(4));
    list->swap_node(list->find_node_by_data(2), list->find_node_by_pos(1));
    list->print_list();
}

void test5()
{
    LinkedList< size_t > *list = new LinkedList< size_t >;
    size_t arr[] = {2, 1, 3};
    for (size_t i : arr)
    {
        list->tail_insert(i);
    }
    list->insertion_sort();
    list->print_list();
    cout << '\n'
         << *list->find_node_by_pos(1) << ' '
         << *list->find_node_by_pos(list->size());
}

void test6()
{
    LinkedList< size_t > list;
    list.tail_insert(1);
    list.tail_insert(5);
    list.tail_insert(3);
    list.move_after(list.find_node_by_data(3), list.find_node_by_data(1));
    list.move_before(list.find_node_by_data(5), list.find_node_by_data(1));
    list.move_before(list.find_node_by_data(3), list.find_node_by_data(5));
    list.print_list();
}

void test7()
{
    LinkedList< size_t > list;
    for (size_t i = 0; i < 10; i++)
    {
        list.tail_insert(i);
    }
    // for (auto ite = list.begin(); ite != list.end(); ++ite)
    // {
    //     cout << *ite;
    // }

    // for (auto ite = list.rbegin(); ite != list.rend(); --ite)
    // {
    //     cout << *ite;
    // }

    // for (const auto i : list)
    // {
    //     cout << i;
    // }

    auto ite = list.begin();
    auto ite2 = ite + 5;
    auto ite3 = ite2 - 2;
    cout << ite2.distance(ite3);
}

void test8()
{
    LinkedList< size_t > ls;
    for (size_t i = 1; i < 11; ++i)
    {
        ls.tail_insert(i);
    }
    auto ite1 = ls.begin();
    ite1 += 5;
    ite1 -= 3;
    auto ite2 = ls.end();
    LinkedList< size_t > ls2(ite1, ite2);
    ls2.insert_before(1, ls2.begin());
    ls2.insert_after(2, ls2.begin());
    ls2.print_list();
}
void test9()
{
    LinkedList< int > ls;
    for (int i = 1; i <= 10; ++i)
    {
        ls.tail_insert(i);
    }
    auto mid = ls.mid(ls.begin(), ls.end());
    auto mid2 = ls.mid(ls.begin(), mid);
    auto mid3 = ls.mid(mid, ls.end());
    auto mid4 = ls.mid(mid2, mid3);
    cout << *mid4;
}

void test10()
{
    LinkedList< int > ls;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(1, 100000);
    for (int i = 1; i < 100000; ++i)
    {
        ls.tail_insert(distribution(gen));
    }

    // ls.insertion_sort();
    ls.merge_sort();
    // O(n^2) 和  O(n*logn),
    // 10万个数两者的速度差了20倍，而随着数据量的增大这个差距会越来越大，这就是算法的力量！
    ls.print_list();
}

int main()
{
    test10();
};
