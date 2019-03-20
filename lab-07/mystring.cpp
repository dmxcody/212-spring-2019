#include "mystring.hpp"

MyString::MyString()
{

}

MyString::MyString(const char*)
{

}


MyString::~MyString()
{

}

uint MyString::len()
{

	return 0;
}

void MyString::set(int, char) 
{
	return;
}

const char MyString::get(int) 
{
	return (const char)0;
}

void MyString::del(int)
{
	return;
}

const char *MyString::substr(int, int)
{ 
	return (const char*)"";
}

char* MyString::c_str()
{
	return (char*)"";
}

void MyString::reverse()
{
	return;
}

uint MyString::find_first(char)
{

	return 0;
}

uint MyString::find_first(const char*)
{

	return 0;
}

uint MyString::find_last(char)
{

	return 0;
}

uint MyString::find_last(const char*)
{

	return 0;
}
int MyString::compare(const char*)
{

	return 0;
}

void MyString::append(const char*)
{
	return;
}

void MyString::append(const char)
{
	return;
}
