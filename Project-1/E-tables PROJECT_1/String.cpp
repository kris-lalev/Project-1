#include "String.h"
#pragma warning (disable : 4996)

String::String()
{
	capacity = 4;
	str = new char[capacity] {' '};
	curr_el = 0;
}

String::String(const String& other)
{
	copy_from(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copy_from(other);
	}
	return *this;
}

String::~String()
{
	free();
}

void String::copy_from(const String& other)
{
	capacity = other.capacity;
	curr_el = other.curr_el;
	str = new char[capacity + 1];
	strcpy(str, other.str);
}

void String::free()
{
	delete[] str;
}

void String::resize()
{
	capacity *= 2;
	char* new_arr = new char[capacity];
	strcpy(new_arr, str);
	free();
	str = new_arr;
}

void String::push_back(char element)
{
	if (curr_el == capacity - 1)
		resize();
	str[curr_el] = element;
	curr_el++;
	str[curr_el] = '\0';
}

void String::set_str(const char* str)
{
	delete[] this->str;
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);

	capacity = strlen(str);
	curr_el = strlen(str);
}

const char* String::get_str() const
{
	return str;
}

void String::print() const
{
	std::cout << str;
}