
#include "DynamicCharArray.h"


DynamicCharArray::DynamicCharArray() = default;
DynamicCharArray::DynamicCharArray(size_t size) :
    m_arr{ new char[size] {} },
    m_size{ size },
    m_capacity{ size }
{}

DynamicCharArray::~DynamicCharArray()
{
    delete[] m_arr;
}

DynamicCharArray::DynamicCharArray(const DynamicCharArray & other) :
    m_arr{ new char[other.m_capacity] },
    m_size{ other.m_size },
    m_capacity{ other.m_capacity }
{
    std::strcpy(begin(), other.begin());
}

DynamicCharArray& DynamicCharArray::operator=(const DynamicCharArray & other)
{
    delete[] m_arr;
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_arr = new char[m_capacity];
    std::strcpy(begin(), other.begin());
    return *this;
}

void DynamicCharArray::push_back(char element)
{
    if (m_size + 2 >= m_capacity)
    {
        extend();
    }
    m_arr[m_size++] = element;
    m_arr[m_size] = '\0';
}

size_t DynamicCharArray::size() const
{
    return m_size;
}

size_t DynamicCharArray::capacity() const
{
    return m_capacity;
}

char* DynamicCharArray::begin()
{
    return m_arr;
}

char* DynamicCharArray::end()
{
    return m_arr + m_size;
}

const char* DynamicCharArray::begin() const
{
    return m_arr;
}

const char* DynamicCharArray::get_char() const
{
    return m_arr;
}

const char* DynamicCharArray::end() const
{
    return m_arr + m_size;
}

void DynamicCharArray::reserve(size_t capacity)
{
    if (capacity > m_capacity)
    {
        resize(capacity);
    }
}

void DynamicCharArray::swap(DynamicCharArray & other)
{
    using std::swap;
    swap(m_arr, other.m_arr);
    swap(m_size, other.m_size);
    swap(m_capacity, other.m_capacity);
}

bool DynamicCharArray::operator==(const DynamicCharArray & other) const
{
    return m_size == other.m_size &&
        std::equal(begin(), end(), other.begin());
}

void DynamicCharArray::extend()
{
    resize(m_capacity * 3 / 2 + 1);
}

void DynamicCharArray::resize(size_t capacity)
{
    m_capacity = capacity + 1;

    char* new_m_arr{ new char[m_capacity] {'\0'} };
    std::copy(begin(), end(), new_m_arr);
    delete[] m_arr;
    m_arr = new_m_arr;
    m_arr[capacity] = '\0';
}

