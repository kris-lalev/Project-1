#pragma once
#include <iostream>
#pragma warning(disable : 4996)

class DynamicCharArray
{
public:
    DynamicCharArray();
    DynamicCharArray(size_t size);
    ~DynamicCharArray();
    DynamicCharArray(const DynamicCharArray& other);
    DynamicCharArray& operator=(const DynamicCharArray& other);

    void push_back(char element);
    size_t size() const;
    size_t capacity() const;
    char* begin();
    char* end();
    const char* begin() const;
    const char* get_char() const;
    const char* end() const;
    void reserve(size_t capacity);
    void swap(DynamicCharArray& other);
    bool operator==(const DynamicCharArray& other) const;
private:
    char* m_arr{ nullptr };
    size_t m_size{ 0 };
    size_t m_capacity{ 0 };

    void extend();

    void resize(size_t capacity);
};
