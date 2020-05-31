#include <iostream>
#pragma warning (disable : 4996)

/**
* This class is the programmers implementation of string(a dynamic cahr array).
* Most of the data in the project is of type String and is transformed when printing.
* @see String(const String& other) @see String& operator=(const String& other) @see ~String()
*/
class String
{
private:
	char* str;
	int curr_el;
	int capacity;
	void copy_from(const String& other);
	void free();
	void resize();

public:
	/**
	* Rule of three.
	* @see String(const String& other) @see String& operator=(const String& other) @see ~String()
	*/
	String();
	String(const String& other);
	String& operator=(const String& other);
	~String();

	void push_back(char element);

	void set_str(const char* str);
	const char* get_str() const;

	void print() const;
};