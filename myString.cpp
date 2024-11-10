#include <cmath>
#include <csetjmp>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>
using std::cout;

class myStr
{
    friend std::ostream &operator<<(std::ostream &osm, const myStr &str);
private:
    static constexpr uint8_t sso_capacity = 17;
    // Small string optimization 在栈区存储小串以提高性能
    char sso_data_[sso_capacity + 1];
    uint16_t size_;
    uint16_t capacity_ = sso_capacity;
    static constexpr uint16_t limits =
        std::numeric_limits< decltype(capacity_) >::max();
    bool useHeap_;
    char *data_;

    // for search sub-str
    static std::unique_ptr< uint16_t[] > computLPS(const char *pattern)
    {
        const uint16_t pat_len = strlen(pattern);
        std::unique_ptr< uint16_t[] > lps_array =
            std::make_unique< uint16_t[] >(pat_len);
        uint16_t lps_len = 0;  // Length of the previous longest prefix suffix
        uint16_t idx = 1;

        while (idx < pat_len)
        {
            if (pattern[idx] == pattern[lps_len])
            {
                ++lps_len;
                lps_array[idx] = lps_len;
                ++idx;
            } else
            {
                if (lps_len != 0)
                {
                    lps_len = lps_array[lps_len - 1];
                } else
                {
                    lps_array[idx] = 0;
                    ++idx;
                }
            }
        }
        return lps_array;
    }

    // for searching char
    static bool is_in_pattern(const char *pattern, const char &ch)
    {
        uint16_t pattern_len = strlen(pattern);
        for (uint16_t i = 0; i < pattern_len; ++i)
        {
            if (pattern[i] == ch)
            {
                return true;
            }
        }
        return false;
    };

    // for sort
    static void insertion_sort_asc(char *data, int left, int right)
    {
        for (int i = left + 1; i <= right; ++i)
        {
            char key = data[i];
            int pre_idx = i - 1;
            while (pre_idx >= left and data[pre_idx] > key)
            {
                data[pre_idx + 1] = data[pre_idx];
                --pre_idx;
            }
            data[pre_idx + 1] = key;
        }
    }

    static void insertion_sort_desc(char *data, int left, int right)
    {
        for (int i = left + 1; i <= right; ++i)
        {
            char key = data[i];
            int pre_idx = i - 1;
            while (pre_idx >= left and data[pre_idx] < key)
            {
                data[pre_idx + 1] = data[pre_idx];
                --pre_idx;
            }
            data[pre_idx + 1] = key;
        }
    }

    static int median_of_three_asc(char *data, int left, int right)
    {
        int mid = (left + right) >> 1;
        if (data[left] > data[mid])
        {
            std::swap(data[left], data[mid]);
        }
        if (data[left] > data[right])
        {
            std::swap(data[left], data[right]);
        }
        if (data[mid] > data[right])
        {
            std::swap(data[mid], data[right]);
        }

        std::swap(data[mid], data[right - 1]);

        return right - 1;
    }

    static int median_of_three_desc(char *data, int left, int right)
    {
        int mid = (left + right) >> 1;
        if (data[left] < data[mid])
        {
            std::swap(data[left], data[mid]);
        }
        if (data[left] < data[right])
        {
            std::swap(data[left], data[right]);
        }
        if (data[mid] < data[right])
        {
            std::swap(data[mid], data[right]);
        }

        std::swap(data[mid], data[right - 1]);

        return right - 1;
    }

    static uint16_t partition_asc(char *data, int left, int right)
    {
        int pivot_idx = median_of_three_asc(data, left, right);
        char pivot = data[pivot_idx];

        int left_boundary = left;
        int right_boundary = right - 1;

        while (true)
        {
            while (left_boundary < right_boundary and
                   data[++left_boundary] < pivot)
            {
            }
            while (right_boundary > left_boundary and
                   data[--right_boundary] > pivot)
            {
            }

            if (left_boundary < right_boundary)
            {
                std::swap(data[left_boundary], data[right_boundary]);
            } else
            {
                break;
            }
        }

        std::swap(data[left_boundary], data[right - 1]);

        return left_boundary;
    }

    static uint16_t partition_desc(char *data, int left, int right)
    {
        int pivot_idx = median_of_three_desc(data, left, right);
        char pivot = data[pivot_idx];

        int left_boundary = left;
        int right_boundary = right - 1;

        while (true)
        {
            while (left_boundary < right_boundary and
                   data[++left_boundary] > pivot)
            {
            }
            while (right_boundary > left_boundary and
                   data[--right_boundary] < pivot)
            {
            }

            if (left_boundary < right_boundary)
            {
                std::swap(data[left_boundary], data[right_boundary]);
            } else
            {
                break;
            }
        }

        std::swap(data[left_boundary], data[right - 1]);

        return left_boundary;
    }

    static void quick_sort_asc(char *data, int left, int right)
    {
        if (left + sso_capacity <= right)
        {
            int pivot_idx = partition_asc(data, left, right);

            quick_sort_asc(data, left, pivot_idx - 1);
            quick_sort_asc(data, pivot_idx + 1, right);
        } else
        {
            insertion_sort_asc(data, left, right);
        }
    }

    static void quick_sort_desc(char *data, int left, int right)
    {
        if (left + sso_capacity <= right)
        {
            int pivot_idx = partition_desc(data, left, right);

            quick_sort_desc(data, left, pivot_idx - 1);
            quick_sort_desc(data, pivot_idx + 1, right);
        } else
        {
            insertion_sort_desc(data, left, right);
        }
    }
public:
    class Iterator
    {
    private:
        myStr &str;
        uint16_t index;
    public:
        // Iterator
        Iterator(myStr &str, uint16_t index) : str(str), index(index){};

        char operator*() const
        {
            if (index >= str.size_)
            {
                throw std::out_of_range("Index out of range at deReference");
            }
            return str.useHeap_ ? str.data_[index] : str.sso_data_[index];
        }

        bool operator==(const Iterator &other) const
        {
            return index == other.index and &str == &other.str;
        }

        bool operator!=(const Iterator &other) const
        {
            return index != other.index or &str != &other.str;
        }

        Iterator &operator++()
        {
            ++index;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++index;
            return temp;
        }

        Iterator &operator--()
        {
            --index;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp = *this;
            --index;
            return temp;
        }

        Iterator operator+(uint16_t distance)
        {
            Iterator temp = *this;
            temp.index += distance;
            return temp;
        }

        Iterator &operator+=(uint16_t distance)
        {
            index += distance;
            return *this;
        }

        Iterator operator-(uint16_t distance)
        {
            Iterator temp = *this;
            temp.index -= distance;
            return temp;
        }

        Iterator operator-=(uint16_t distance)
        {
            index -= distance;
            return *this;
        }

        int distance(const Iterator &other) const
        {
            if (&str != &other.str)
            {
                throw std::invalid_argument(
                    "Iterators belong to different objects");
            }
            return static_cast< int >(index - other.index);
        }

        uint16_t get_position() const
        {
            return index;
        }

        bool is_sameString(const Iterator &other) const
        {
            return &str == &other.str;
        }
    };

    // Member function
    myStr() : useHeap_(false), size_(0), data_(nullptr), sso_data_(""){};

    myStr(const char *str)
        : size_(0), data_(nullptr), useHeap_(false), sso_data_("")
    {
        *this = str;
    }

    myStr(Iterator left, Iterator right)
        : size_(0), data_(nullptr), useHeap_(false)
    {
        if (!left.is_sameString(right))
        {
            throw std::invalid_argument(
                "Two Iterators belong to different myStr");
        }
        if (left.get_position() > right.get_position())
        {
            throw std::invalid_argument(
                "Left Iterator must be before right Iterator");
        }

        size_ = right.get_position() - left.get_position();
        if (size_ < sso_capacity)
        {
            useHeap_ = false;
            for (uint16_t i = 0; i < size_; ++i)
            {
                sso_data_[i] = *left;
                ++left;
            }
            sso_data_[size_] = '\0';
        } else
        {
            useHeap_ = true;
            capacity_ = (size_ * 2 + 1 < limits) ? size_ * 2 + 1 : limits;
            try
            {
                data_ = new char[capacity_];
                for (uint16_t i = 0; i < size_; ++i)
                {
                    data_[i] = *left;
                    ++left;
                }
                data_[size_] = '\0';
            }
            catch (const std::bad_alloc &)
            {
                throw std::runtime_error(
                    "Memory allocation error at `range_constructor`");
            }
        }
    }

    myStr(const myStr &other)
        : useHeap_(other.useHeap_), size_(other.size_),
          capacity_(other.capacity_), data_(nullptr)
    {
        if (useHeap_)
        {
            try
            {
                data_ = new char[capacity_];
                strcpy(data_, other.data_);
            }
            catch (std::bad_alloc &)
            {
                throw std::runtime_error("Memory allocation error");
            }
        } else
        {
            strcpy(sso_data_, other.sso_data_);
        }
    }

    // operator= for const char*
    myStr &operator=(const char *str)
    {
        uint32_t str_len = strlen(str);
        if (str_len > limits)
        {
            throw std::out_of_range("String Exceeds limits");
        }

        // if str lt sso_capacity, it't not need allocate memory and it's need
        // to free memory which had allocated.
        if (str_len < sso_capacity)
        {
            if (useHeap_)
            {
                delete[] data_;
                data_ = nullptr;
                strcpy(sso_data_, str);
            } else
            {
                strcpy(sso_data_, str);
            }

        }
        // case need allocate memory
        else
        {
            // case dont't need re-allocate memory
            if (capacity_ > str_len)
            {
                strcpy(data_, str);
            } else
            {
                if (useHeap_)
                {
                    // re-allocate memory
                    delete[] data_;
                    capacity_ =
                        (str_len * 2 + 1) < limits ? str_len * 2 + 1 : limits;
                    try
                    {
                        data_ = new char[capacity_];
                        strcpy(data_, str);
                    }
                    catch (std::bad_alloc &)
                    {
                        throw std::runtime_error("Memory allocation error");
                    }
                } else
                {
                    // allocate memory
                    useHeap_ = true;
                    capacity_ =
                        (str_len * 2 + 1) < limits ? str_len * 2 + 1 : limits;
                    try
                    {
                        data_ = new char[capacity_];
                        strcpy(data_, str);
                    }
                    catch (std::bad_alloc &)
                    {
                        throw std::runtime_error("Memory allocation error");
                    }
                }
            }
        }
        size_ = str_len;

        return *this;
    }

    // operator= for other myStr
    myStr &operator=(const myStr &other)
    {
        // self-check for avoid memory leak
        if (this == &other)
        {
            return *this;
        }
        if (useHeap_)
        {
            delete[] data_;
            data_ = nullptr;
        }

        useHeap_ = other.useHeap_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        if (useHeap_)
        {
            try
            {
                data_ = new char[capacity_];
                strcpy(data_, other.data_);
            }
            catch (std::bad_alloc &)
            {
                throw std::runtime_error("Memory allocation error");
            }
        } else
        {
            strcpy(sso_data_, other.sso_data_);
        }

        return *this;
    }

    myStr(myStr &&other) noexcept
        : useHeap_(other.useHeap_), size_(other.size_),
          capacity_(other.capacity_), data_(other.data_)
    {
        strcpy(sso_data_, other.sso_data_);
        other.size_ = 0;
        other.capacity_ = 0;
        other.useHeap_ = false;
        other.data_ = nullptr;
    }

    ~myStr()
    {
        clear();
    }

    char &operator[](uint16_t index)
    {
        // If it's necessary for range checking
        // if (index >= size_)
        // {
        //     throw std::out_of_range("out_of_range");
        // }
        return useHeap_ ? data_[index] : sso_data_[index];
    }

    const char &operator[](uint16_t index) const
    {
        return useHeap_ ? data_[index] : sso_data_[index];
    }

    bool operator==(const myStr &other) const
    {
        if (size_ != other.size_)
        {
            return false;
        }

        for (uint16_t i = 0; i < size_; ++i)
        {
            char left_char = useHeap_ ? data_[i] : sso_data_[i];
            char right_char =
                other.useHeap_ ? other.data_[i] : other.sso_data_[i];

            if (left_char != right_char)
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const myStr &other) const
    {
        if (size_ != other.size_)
        {
            return true;
        }

        for (uint16_t i = 0; i < size_; ++i)
        {
            char left_char = useHeap_ ? data_[i] : sso_data_[i];
            char right_char =
                other.useHeap_ ? other.data_[i] : other.sso_data_[i];

            if (left_char != right_char)
            {
                return true;
            }
        }

        return false;
    }

    myStr operator+(const char ch) const
    {
        myStr temp = *this;
        uint32_t new_size = size_ + 1;
        if (new_size > limits)
        {
            throw std::out_of_range("String Exceeds limit");
        }

        // sso_capacity still enough for appending string
        if (new_size <= sso_capacity)
        {
            temp[size_] = ch;
            temp[size_ + 1] = '\0';
        }
        // sso_capacity not enough
        else if (useHeap_)
        {
            // data left capacity is enought for expanding string
            if (capacity_ > new_size)
            {
                temp[size_] = ch;
                temp[size_ + 1] = '\0';
            }
            // data left capacity isn't enough, so re-allocate memory for
            // expanding string and free old data memory
            else
            {
                temp.capacity_ =
                    (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
                char *new_data = new char[capacity_];
                strcpy(new_data, data_);
                delete[] temp.data_;
                temp.data_ = new_data;
                temp[size_] = ch;
                temp[size_ + 1] = '\0';
            }

        }
        // sso_capacity isn't enough, and data need use heap
        else
        {
            temp.useHeap_ = true;
            temp.capacity_ =
                (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
            temp.data_ = new char[temp.capacity_];
            strcpy(temp.data_, temp.sso_data_);
            temp[size_] = ch;
            temp[size_ + 1] = '\0';
        }
        temp.size_ = new_size;

        return temp;
    }

    myStr operator+(const char *str) const
    {
        myStr temp = *this;
        uint16_t expand_size = strlen(str);
        uint32_t new_size = size_ + expand_size;
        if (new_size > limits)
        {
            throw std::out_of_range("String Exceeds limit");
        }

        // sso_capacity still enough for appending string
        if (new_size <= sso_capacity)
        {
            strcpy(&temp.sso_data_[temp.size_], str);

        }
        // sso_capacity not enough
        else if (useHeap_)
        {
            uint16_t left_capacity = capacity_ - size_;
            // data left capacity is enought for expanding string
            if (left_capacity > expand_size)
            {
                strcpy(&temp.data_[size_], str);
            }
            // data left capacity isn't enough, so re-allocate memory for
            // expanding string and free old data memory
            else
            {
                temp.capacity_ =
                    (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
                char *new_data = new char[capacity_];
                strcpy(new_data, data_);
                strcpy(&new_data[size_], str);
                delete[] temp.data_;
                temp.data_ = new_data;
            }

        }
        // sso_capacity isn't enough, and data need use heap
        else
        {
            temp.useHeap_ = true;
            temp.capacity_ =
                (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
            temp.data_ = new char[temp.capacity_];
            strcpy(temp.data_, temp.sso_data_);
            strcpy(&temp.data_[temp.size_], str);
        }
        temp.size_ = new_size;

        return temp;
    }

    myStr operator+(const myStr &other) const
    {
        return *this + (other.useHeap_ ? other.data_ : other.sso_data_);
    }

    myStr &operator+=(const char ch)
    {
        push_back(ch);

        return *this;
    }

    myStr &operator+=(const char *str)
    {
        uint16_t expansion_size = strlen(str);
        uint32_t new_size = size_ + expansion_size;
        if (new_size > limits)
        {
            throw std::out_of_range("String Exceeds limit");
        }

        // sso_capacity still enough for appending string
        if (new_size <= sso_capacity)
        {
            strcpy(&sso_data_[size_], str);

        }
        // sso_capacity not enough
        else if (useHeap_)
        {
            uint16_t left_capacity = capacity_ - size_;
            // data left capacity is enought for expanding string
            if (left_capacity > expansion_size)
            {
                strcpy(&data_[size_], str);
            }
            // data left capacity isn't enough, so re-allocate memory for
            // expanding string and free old data memory
            else
            {
                capacity_ =
                    (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
                char *new_data = new char[capacity_];
                strcpy(new_data, data_);
                strcpy(&new_data[size_], str);
                delete[] data_;
                data_ = new_data;
            }

        }
        // sso_capacity isn't enough, and data need use heap
        else
        {
            useHeap_ = true;
            capacity_ =
                (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
            data_ = new char[capacity_];
            strcpy(data_, sso_data_);
            strcpy(&data_[size_], str);
        }
        size_ = new_size;

        return *this;
    }

    myStr &operator+=(const myStr &other)
    {
        return *this += (other.useHeap_ ? other.data_ : other.sso_data_);
    }

    Iterator begin()
    {
        return Iterator(*this, 0);
    }

    Iterator end()
    {
        return Iterator(*this, size_);
    }

    Iterator rbegin()
    {
        return Iterator(*this, size_ - 1);
    }

    Iterator rend()
    {
        return Iterator(*this, -1);
    }

    uint16_t length() const
    {
        return size_;
    }

    uint16_t capacity() const
    {
        return capacity_;
    }

    uint16_t size() const
    {
        return size_;
    }

    const char *data()
    {
        return useHeap_ ? data_ : sso_data_;
    }

    // Reserve memory which eq new_capacity.
    void reserve(const uint16_t new_capacity)
    {
        if (capacity_ < new_capacity)
        {
            char *new_data =
                new char[new_capacity < limits ? new_capacity : limits];
            if (useHeap_)
            {
                strcpy(new_data, data_);
                delete[] data_;  // 分析删除现有 data_

            } else
            {
                strcpy(new_data, sso_data_);
            }
            data_ = new_data;
            capacity_ = new_capacity;
            useHeap_ = true;
        }
    }

    // change size of myStr obj. If new_size > siez_, then the left chars filled
    // by fill_char;
    //  If new_size < size_, then the str is truncated to new_size;
    // @param[in]  new_size
    // @param[in]  fill_char
    void resize(const uint16_t new_size, const char fill_char = '\0')
    {
        // need to re-allocate memory
        if (new_size > capacity_)
        {
            capacity_ = (new_size * 2 + 1) < limits ? new_size * 2 + 1 : limits;
            char *new_data_ = new char[capacity_];
            strcpy(new_data_, useHeap_ ? data_ : sso_data_);
            if (useHeap_)
            {
                delete[] data_;
            }
            data_ = new_data_;
            useHeap_ = true;

            for (uint16_t i = size_; i < new_size; ++i)
            {
                data_[i] = fill_char;
            }
            size_ = new_size;
        }
        // new_size < capacity_ , so there is no need to re-allocate memory.
        // Just fill new char or truncate str.
        else
        {
            if (new_size > size_)
            {
                for (uint16_t i = size_; i < new_size; ++i)
                {
                    useHeap_ ? data_[i] = fill_char : sso_data_[i] = fill_char;
                }
            } else
            {
                useHeap_ ? data_[new_size] = '\0' : sso_data_[new_size] = '\0';
            }
        }
        size_ = new_size;
    }

    /**
     * @brief      push a char in the front of this string. O(n)
     *
     * @param[in]  ch    inserted char
     *
     * @return     Reference of this string
     */
    myStr &push_front(const char ch)
    {
        uint32_t new_size = size_ + 1;
        if (new_size > limits)
        {
            throw std::out_of_range("String Exceeds limit at `push_front`");
        }

        // sso_capacity still enough for appending string
        if (new_size <= sso_capacity)
        {
            memmove(&sso_data_[1], &sso_data_[0], size_);
            sso_data_[0] = ch;
            sso_data_[new_size] = '\0';
        }
        // sso_capacity not enough
        else if (useHeap_)
        {
            // data left capacity is enought for expanding string
            if (capacity_ > new_size)
            {
                memmove(&data_[1], &data_[0], size_);
                data_[0] = ch;
                data_[new_size] = '\0';
            }
            // data left capacity isn't enough, so re-allocate memory for
            // expanding string and free old data memory
            else
            {
                capacity_ =
                    (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
                char *new_data = new char[capacity_];
                new_data[0] = ch;
                strcpy(&new_data[1], data_);
                new_data[new_size] = '\0';
                delete[] data_;
                data_ = new_data;
            }
        }
        // sso_capacity isn't enough, and data need use heap
        else
        {
            useHeap_ = true;
            capacity_ =
                (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
            data_ = new char[capacity_];
            data_[0] = ch;
            strcpy(&data_[1], sso_data_);
            data_[new_size] = '\0';
        }
        size_ = new_size;

        return *this;
    }

    /**
     * @brief      push a char end of this string
     *
     * @param[in]  ch    Inserted char
     *
     * @return     Ref of this string
     */
    myStr &push_back(const char ch)
    {
        uint32_t new_size = size_ + 1;
        if (new_size > limits)
        {
            throw std::out_of_range("String Exceeds limit at `push_back`");
        }

        // sso_capacity still enough for appending string
        if (new_size <= sso_capacity)
        {
            sso_data_[size_] = ch;
            sso_data_[new_size] = '\0';
        }
        // sso_capacity not enough
        else if (useHeap_)
        {
            // data left capacity is enought for expanding string
            if (capacity_ > new_size)
            {
                data_[size_] = ch;
                data_[new_size] = '\0';
            }
            // data left capacity isn't enough, so re-allocate memory for
            // expanding string and free old data memory
            else
            {
                capacity_ =
                    (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
                char *new_data = new char[capacity_];
                strcpy(new_data, data_);
                delete[] data_;
                data_ = new_data;
                data_[size_] = ch;
                data_[new_size] = '\0';
            }

        }
        // sso_capacity isn't enough, and data need use heap
        else
        {
            useHeap_ = true;
            capacity_ =
                (new_size * 2 + 1) < limits ? (new_size * 2 + 1) : limits;
            data_ = new char[capacity_];
            strcpy(data_, sso_data_);
            data_[size_] = ch;
            data_[new_size] = '\0';
        }
        size_ = new_size;

        return *this;
    }

    myStr &append(const char ch)
    {
        return *this += ch;
    }

    myStr &append(const char *str)
    {
        return *this += str;
    }

    myStr &append(const myStr &other)
    {
        return *this += (other.useHeap_ ? other.data_ : other.sso_data_);
    }

    // Count how many the specific characters in %String
    uint16_t head_count(const char &character) const
    {
        uint16_t nums{};
        for (uint16_t i = 0; i < size_; ++i)
        {
            if ((useHeap_ ? data_[i] : sso_data_[i]) == character)
            {
                ++nums;
            }
        }
        return nums;
    }

    /**
     * @brief      Find a char in `pattern` from `sting`
     *
     * @param[in]  pattern    match pattern
     * @param[in]  start_pos  start position for search
     * @param[in]  n          nums of matehed char
     *
     * @return     If find it, then return he index of No.n Char. If not find,
     * return -1
     */
    int find_char_in(const char *pattern, const uint16_t start_pos = 0,
                     const uint16_t n = 1) const
    {
        uint16_t count = 0;
        for (uint16_t i = start_pos; i < size_; ++i)
        {
            if (is_in_pattern(pattern, (*this)[i]))
            {
                ++count;
                if (count == n)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    /**
     * @brief      Find a char not in `pattern`
     *
     * @param[in]  pattern    match pattern
     * @param[in]  start_pos  start position for search
     * @param[in]  n          nums of char not in pattern
     *
     * @return     If not in pattern, then return the index of No.n Char. If all
     * chars in pattern , return -1
     */
    int find_char_not_in(const char *pattern, const uint16_t start_pos = 0,
                         const uint16_t n = 1) const
    {
        uint16_t count = 0;
        for (uint16_t i = start_pos; i < size_; ++i)
        {
            if (!is_in_pattern(pattern, (*this)[i]))
            {
                ++count;
                if (count == n)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    /**
     * @brief      Match No.n substr in %String
     *
     * @param[in]  substr     str to find
     * @param[in]  start_pos  start position for search
     * @param[in]  n          No.n in String
     *
     * @return     If match return first char's index of substr. If not match ,
     *             return -1
     */
    int find_substr(const char *substr, const uint16_t start_pos = 0,
                    const uint16_t n = 1) const
    {
        std::unique_ptr< uint16_t[] > lps_array = computLPS(substr);
        const char *text = useHeap_ ? data_ : sso_data_;
        uint16_t num = 0;
        uint16_t sub_len = strlen(substr);

        uint16_t text_idx = start_pos;
        uint16_t sub_idx = 0;

        while (text_idx < size_)
        {
            if (text[text_idx] == substr[sub_idx])
            {
                ++text_idx;
                ++sub_idx;

                if (sub_idx == sub_len)
                {
                    ++num;
                    if (num == n)
                    {
                        return text_idx - sub_idx;
                    }
                }
            } else
            {
                if (sub_idx != 0)
                {
                    sub_idx = lps_array[sub_idx - 1];
                } else
                {
                    ++text_idx;
                }
            }
        }

        return -1;
    }

    /**
     * @brief      Match No.n substr in %String
     *
     * @param      other      substr to find
     * @param[in]  start_pos  start position for search
     * @param[in]  n          No.n in String
     *
     * @return     If match return first char's index of substr. If not match ,
     *             return -1
     */
    int find_substr(myStr &other, const uint16_t start_pos = 0,
                    const uint16_t n = 1) const
    {
        const char *substr = other.data();
        return find_substr(substr, start_pos, n);
    }

    /**
     * @brief      Finds all substr in %String
     *
     * @param[in]  substr     pattern
     * @param[in]  start_pos  start position for search
     *
     * @return     return a vector which contains every substr's first char
     *             index
     */
    std::vector< int > find_all_substr(const char *substr,
                                       const uint16_t start_pos) const
    {
        std::vector< int > result;
        std::unique_ptr< uint16_t[] > lps_array = computLPS(substr);
        const char *text = useHeap_ ? data_ : sso_data_;

        uint16_t sub_len = strlen(substr);
        uint16_t text_idx = start_pos;
        uint16_t sub_idx = 0;

        while (text_idx < size_)
        {
            if (text[text_idx] == substr[sub_idx])
            {
                ++text_idx;
                ++sub_idx;

                if (sub_idx == sub_len)
                {
                    result.push_back(text_idx - sub_idx);
                    sub_idx = 0;  // reset to 0 to avoid reusing characters
                }
            } else
            {
                if (sub_idx != 0)
                {
                    sub_idx = lps_array[sub_idx - 1];
                } else
                {
                    ++text_idx;
                }
            }
        }
        return result;
    }

    /**
     * @brief      Finds all substr in %String
     *
     * @param      other      substr to find
     * @param[in]  start_pos  start position fo search
     *
     * @return     return a vector which contains every substr's first char
     *             index
     */
    std::vector< int > find_all_substr(myStr &other,
                                       const uint16_t start_pos) const
    {
        const char *substr = other.data();
        return find_all_substr(substr, start_pos);
    }

    /**
     * @brief      insert substr at position
     *
     * @param[in]  position  -
     * @param[in]  str       substr
     *
     * @return     Reference of this string
     */
    myStr &insert(uint16_t position, const char *str)
    {
        uint16_t left_capacity = capacity_ - size_;
        uint16_t expansion_size = strlen(str);
        uint16_t new_size =
            size_ + expansion_size < limits ? size_ + expansion_size : limits;

        if (new_size < sso_capacity)
        {
            memmove(&sso_data_[position + expansion_size], &sso_data_[position],
                    size_ - position);
            strncpy(&sso_data_[position], str, expansion_size);
            size_ = new_size;
        } else
        {
            if (useHeap_)
            {
                // capacity is enough for insert substr
                if (left_capacity > expansion_size)
                {
                    memmove(&data_[position + expansion_size], &data_[position],
                            size_ - position);
                    strncpy(&data_[position], str, expansion_size);
                    size_ = new_size;
                }
                // capacity is not enough for insert substr
                else
                {
                    capacity_ =
                        new_size * 2 + 1 < limits ? new_size * 2 + 1 : limits;
                    try
                    {
                        char *new_data_ = new char[capacity_];
                        strncpy(new_data_, data_, position);
                        strncpy(&new_data_[position], str, expansion_size);
                        strcpy(&new_data_[position + expansion_size],
                               &data_[position]);
                        delete[] data_;
                        size_ = new_size;
                        data_ = new_data_;
                    }
                    catch (std::bad_alloc &)
                    {
                        throw std::runtime_error("Memory allocation error");
                    }
                }
            }
            // not use heap, but now it need use heap
            else
            {
                useHeap_ = true;
                capacity_ =
                    new_size * 2 + 1 < limits ? new_size * 2 + 1 : limits;
                try
                {
                    data_ = new char[capacity_];
                    strncpy(data_, sso_data_, position);
                    strncpy(&data_[position], str, expansion_size);
                    strcpy(&data_[position + expansion_size],
                           &sso_data_[position]);
                    size_ = new_size;
                }
                catch (std::bad_alloc &)
                {
                    throw std::runtime_error("Memory allocation error");
                }
            }
        }

        return *this;
    }

    /**
     * @brief      insert substr at position
     *
     * @param[in]  position  insertion position
     * @param      other     The other myStr
     *
     * @return     Reference of this string
     */
    myStr &insert(uint16_t position, myStr &other)
    {
        const char *str = other.data();
        return insert(position, str);
    }

    /**
     * @brief      insert substr at the position of Iterator
     *
     * @param[in]  ite   Insertion position
     * @param[in]  str   substr
     *
     * @return     Reference of this %String
     */
    myStr &insert(const Iterator ite, const char *str)
    {
        uint16_t position = ite.get_position();
        return insert(position, str);
        ;
    }

    /**
     * @brief      insert substr at the position of Iterator
     *
     * @param[in]  ite    Insertion position
     * @param      other  other mystr string
     *
     * @return     Reference of this %String
     */
    myStr &insert(const Iterator ite, myStr &other)
    {
        uint16_t position = ite.get_position();
        const char *str = other.data();
        return insert(position, str);
    }

    /**
     * @brief      delete a char at position
     *
     * @param[in]  position  position of deleted char
     *
     * @return     Ref of this string
     */
    myStr &erase(const uint16_t position)
    {
        if (position < size_)
        {
            if (useHeap_)
            {
                memcpy(&data_[position], &data_[position + 1],
                       size_ - position);
                data_[size_ - 1] = '\0';
            } else
            {
                memcpy(&sso_data_[position], &sso_data_[position + 1],
                       size_ - position);
                sso_data_[size_ - 1] = '\0';
            }
            --size_;
        }

        return *this;
    }

    /**
     * @brief      delete a char at position
     *
     * @param[in]  ite   Iterator of deleted char
     *
     * @return     Ref of this string
     */
    myStr &erase(const Iterator ite)
    {
        uint16_t position = ite.get_position();

        return erase(position);
    }

    /**
     * @brief      Erase `n` chars starting from `start_pos`
     *
     * @param[in]  start_pos  start positon
     * @param[in]  n          nums of erased chars
     *
     * @return     Ref of this `string`
     */
    myStr &erase_range(const uint16_t start_pos, const uint16_t n)
    {
        if (start_pos + n <= size_)
        {
            if (useHeap_)
            {
                memcpy(&data_[start_pos], &data_[start_pos + n],
                       size_ - start_pos - n);
            } else
            {
                memcpy(&sso_data_[start_pos], &sso_data_[start_pos + n],
                       size_ - start_pos - n);
            }
            size_ -= n;
            (*this)[size_] = '\0';
        }
        return *this;
    }

    /**
     * @brief      delete chars if chars in string eq ch
     *
     * @param[in]  ch         deleted char
     * @param[in]  start_pos  start position
     *
     * @return     Ref of this string
     */
    myStr &erase_if(const char ch, uint16_t start_pos = 0)
    {
        if (start_pos < size_)
        {
            uint16_t read_idx = start_pos;
            uint16_t write_idx = start_pos;
            uint16_t count = 0;  // the nums of erased chars

            while (read_idx < size_)
            {
                if ((*this)[read_idx] != ch)
                {
                    (*this)[write_idx] = (*this)[read_idx];
                    ++write_idx;
                } else
                {
                    ++count;
                }
                ++read_idx;
            }

            (*this)[write_idx] = '\0';
            size_ -= count;
        }

        return *this;
    }

    /**
     * @brief      delete chars if chars in string eq ch
     *
     * @param[in]  ch         deleted chars
     * @param[in]  start_ite  start position
     *
     * @return     Ref of this string
     */
    myStr &erase_if(const char ch, Iterator start_ite)
    {
        uint16_t position = start_ite.get_position();

        return erase_if(ch, position);
    }

    /**
     * @brief      Erase chars if the char satisfies 'predict'
     *
     * @param[in]  predict    Judgement function
     * @param[in]  start_pos  -
     *
     * @return     Reference of this string
     */
    myStr &erase_if(const std::function< bool(char) > &predict,
                    uint16_t start_pos = 0)
    {
        if (start_pos < size_)
        {
            uint16_t read_idx = start_pos;
            uint16_t write_idx = start_pos;
            uint16_t count = 0;

            while (read_idx < size_)
            {
                if (!predict((*this)[read_idx]))
                {
                    (*this)[write_idx] = (*this)[read_idx];
                    ++write_idx;
                } else
                {
                    ++count;
                }
                ++read_idx;
            }

            (*this)[write_idx] = '\0';
            size_ -= count;
        }

        return *this;
    }

    /**
     * @brief      replace old_str to new_str
     *
     * @param[in]  old_str        chars to be replaced
     * @param[in]  new_str        new str
     * @param[in]  start_pos      the positon execute replace
     * @param[in]  replace_times  the nums of execution replacement
     *
     * @return     Ref of this string
     */
    myStr &replace(const char *old_str, const char *new_str,
                   const uint16_t start_pos = 0,
                   uint16_t replace_times = limits)
    {
        if (start_pos < size_)
        {
            std::vector< int > substr_indexes =
                find_all_substr(old_str, start_pos);
            if (substr_indexes.empty())
            {
                return *this;
            }

            int old_str_len = strlen(old_str);
            int new_str_len = strlen(new_str);
            uint16_t matched_times = substr_indexes.size();
            replace_times =
                replace_times > matched_times ? matched_times : replace_times;
            uint32_t new_size = size_ - (strlen(old_str) * replace_times) +
                                (strlen(new_str) * replace_times);
            new_size = new_size > limits ? limits : new_size;

            // use stack
            if (new_size < sso_capacity)
            {
                char new_sso_data[sso_capacity]{};

                // process the front part chars
                strncpy(new_sso_data, sso_data_, substr_indexes[0]);

                // prcess the middle part chars
                for (uint16_t i = 0; i < replace_times; ++i)
                {
                    strcpy(&new_sso_data[substr_indexes[i] +
                                         (new_str_len - old_str_len) * i],
                           new_str);
                    if (i != replace_times - 1)
                    {
                        strncpy(&new_sso_data[substr_indexes[i] +
                                              (new_str_len - old_str_len) * i +
                                              new_str_len],
                                &sso_data_[substr_indexes[i] + old_str_len],
                                substr_indexes[i + 1] -
                                    (substr_indexes[i] + old_str_len));
                    }
                }

                // all replacement accomplish, then process the tail substr
                strcpy(
                    &new_sso_data[substr_indexes[replace_times - 1] +
                                  (new_str_len - old_str_len) * replace_times +
                                  old_str_len],
                    &sso_data_[substr_indexes[replace_times - 1] +
                               old_str_len]);

                size_ = new_size;
                new_sso_data[size_] = '\0';
                strcpy(sso_data_, new_sso_data);
            }
            // use heap
            else
            {
                capacity_ =
                    (new_size * 2 + 1) > limits ? (new_size * 2 + 1) : limits;
                char *new_data{};
                try
                {
                    new_data = new char[capacity_];
                }
                catch (const std::bad_alloc &)
                {
                    throw std::runtime_error(
                        "Memory allocation error at `replace`");
                }

                // process the front part chars
                strncpy(new_data, data_, substr_indexes[0]);
                // prcess the middle part chars
                for (uint16_t i = 0; i < replace_times; ++i)
                {
                    strcpy(&new_data[substr_indexes[i] +
                                     (new_str_len - old_str_len) * i],
                           new_str);
                    if (i != replace_times - 1)
                    {
                        strncpy(&new_data[substr_indexes[i] +
                                          (new_str_len - old_str_len) * i +
                                          new_str_len],
                                &data_[substr_indexes[i] + old_str_len],
                                substr_indexes[i + 1] -
                                    (substr_indexes[i] + old_str_len));
                    }
                }

                // all replacement accomplish, then process the tail part
                strcpy(&new_data[substr_indexes[replace_times - 1] +
                                 (new_str_len - old_str_len) * replace_times +
                                 old_str_len],
                       &data_[substr_indexes[replace_times - 1] + old_str_len]);

                size_ = new_size;
                new_data[size_] = '\0';
                delete[] data_;
                data_ = new_data;
            }
        }

        return *this;
    }

    /**
     * @brief      replace old_str to new_str
     *
     * @param[in]  old_str        origin str
     * @param      new_str        Other mystr's data
     * @param[in]  start_pos      the positon execute replace
     * @param[in]  replace_times  the nums of execution replacement
     *
     * @return     Ref of this string
     */
    myStr &replace(const char *old_str, myStr &new_str,
                   const uint16_t start_pos = 0,
                   uint16_t replace_times = limits)

    {
        return replace(old_str, new_str.data(), start_pos, replace_times);
    }

    /**
     * @brief      reverse all chars
     *
     * @return     Ref of this string
     */
    myStr &reverse()
    {
        uint16_t left = 0;
        uint16_t right = size_ - 1;
        while (left < right)
        {
            std::swap((*this)[left++], (*this)[right--]);
        }

        return *this;
    }

    /**
     * @brief      splite `String` by any char in `delimiter` and push all parts
     *             in a Vector
     *
     * @param[in]  delimiter  A string consist of delimiters
     *
     * @return     A Vector
     */
    std::vector< myStr > split(const char *delimiter = " ")
    {
        std::vector< myStr > result;
        int left_pos = find_char_not_in(delimiter);
        int right_pos = find_char_in(delimiter, left_pos);
        while (right_pos != -1)

        {
            result.emplace_back(Iterator(*this, left_pos),
                                Iterator(*this, right_pos));
            left_pos = find_char_not_in(delimiter, right_pos);
            right_pos = find_char_in(delimiter, left_pos);
        }

        if (left_pos != -1)
        {
            result.emplace_back(Iterator(*this, left_pos),
                                Iterator(*this, size_));
        }
        return result;
    }

    /**
     * @brief      Erase `chars` at the part of head and tail of `string` in
     * param `chars`
     *
     * @param[in]  chars  to be erased. Default is space, \t and \n
     *
     * @return     Ref of this `string`
     */
    myStr &strip(const char *chars = " \t\n")
    {
        uint16_t chars_len = strlen(chars);
        uint16_t head_count{};
        uint16_t tail_count{};
        auto is_in_chars = [&](char &ch)
        {
            for (uint16_t i = 0; i < chars_len; ++i)
            {
                if (chars[i] == ch)
                {
                    return true;
                }
            }
            return false;
        };

        for (uint16_t i = 0; i < size_; ++i)
        {
            if (is_in_chars((*this)[i]))
            {
                ++head_count;
            } else
            {
                erase_range(0, head_count);
                break;
            }
        }

        for (int i = size_ - 1; i > 0; --i)
        {
            if (is_in_chars((*this)[i]))
            {
                ++tail_count;
            } else
            {
                erase_range(size_ - tail_count, tail_count);
                break;
            }
        }

        return *this;
    }

    /**
     * @brief      Sort `string` from [`start_pos` to `end_pos`]
     *
     * @param[in]  start_pos  left boundary of sorted range
     * @param[in]  end_pos    right boundary of sorted range
     * @param[in]  method     "Asc" or "Desc"
     *
     * @return     Ref of this `string`
     */
    myStr &sort(uint16_t start_pos = 0, uint16_t end_pos = limits,
                const char *method = "Asc")
    {
        if (end_pos == limits or end_pos >= size_)
        {
            end_pos = size_ - 1;
        }

        bool ascending = (method == "Asc" or method == "asc");
        bool useQuickSort =
            (useHeap_ and (start_pos + sso_capacity <= end_pos));

        if (ascending)
        {
            if (useQuickSort)
            {
                quick_sort_asc(data_, start_pos, end_pos);
            } else
            {
                insertion_sort_asc(sso_data_, start_pos, end_pos);
            }
        } else
        {
            if (useQuickSort)
            {
                quick_sort_desc(data_, start_pos, end_pos);
            } else
            {
                insertion_sort_desc(sso_data_, start_pos, end_pos);
            }
        }

        return *this;
    }

    /**
     * @brief      Free data in heap.
     */
    void clear()
    {
        if (useHeap_ or capacity_ > sso_capacity)
        {
            size_ = 0;
            capacity_ = 0;
            delete[] data_;
            data_ = nullptr;
            useHeap_ = false;
        }
    }

    // --------------
};

std::ostream &operator<<(std::ostream &osm, const myStr &str)
{
    for (uint16_t i = 0; i < str.size(); ++i)
    {
        osm << str[i];
    }
    return osm;
}

char generateRandomChar()
{
    int randValue = rand() % 62;  // 0 到 61 之间的随机数

    if (randValue < 10)
    {
        // 生成数字 0-9
        return '0' + randValue;  // ASCII 48 到 57
    } else if (randValue < 36)
    {
        // 生成大写字母 A-Z
        return 'A' + (randValue - 10);  // ASCII 65 到 90
    } else
    {
        // 生成小写字母 a-z
        return 'a' + (randValue - 36);  // ASCII 97 到 122
    }
}

void test1()
{
    myStr str = "123";
    for (int i = 0; i < 65000; ++i)
    {
        str.push_back(generateRandomChar());
    }
    cout << str.sort(0, str.size(), "asc") << "   len:" << str.size();
}

int main(int argc, char const *argv[])
{
    test1();
    return 0;
}