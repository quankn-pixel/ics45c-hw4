#include "string.hpp"
#include <iostream>
#include <utility>

using namespace std;

// constructor
String::String(const char *s): buf(strdup(s)) {}

// copy constructor
String::String(const String &s): buf(strdup(s.buf)) {}

// move constructor ////
/*
String::String(String &&s) {
	buf = s.buf;
	s.buf = nullptr;
}
*/

void String::swap(String &s) {
	// no std:: needed bc the func signatures are different
	swap(buf, s.buf);
}

// copy assignment operator
String &operator=(String s) {
	delete[] buf;
	buf = strdup(s);
	return *this;
}

// move assigment operator
/*
String &operator=(String &&s) {
	delete[] buf;
	buf = s.buf;
	s.buf = nullptr;
	return *this;
}
*/

char &String::operator[](int index) {
	int length = strlen(buf);
	if (index < 0 || index >= length) {
		cout << "ERROR: Index Out Of Bounds" << endl;
		return buf[0];
	}

	return buf[index];	
}

const char &String::operator[](int index) const {
	int length = strlen(buf);
	if (index < 0 || index >= length) {
		cout << "ERROR: Index Out Of Bounds" << endl;
		return buf[0];
	}

	return buf[index];	
}

int String::size() const {
	return strlen(buf);
}

String String::reverse() const {
	String reversed {*this};
	reverse_cpy(reversed.buf, buf);
	return reversed;
}

// Relational Operators ////////////////////////////////////////////////////////
bool String::operator==(const String &s) const {
return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
	return strcmp(buf, s.buf) != 0;
}

bool String::operator>(const String &s) const {
	return strcmp(buf, s.buf) > 0;
}

bool String::operator<(const String &s) const {
	return strcmp(buf, s.buf) < 0;
}

bool String::operator<=(const String &s) const {
	return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(const String &s) const {
	return strcmp(buf, s.buf) >= 0;
}


// Relational Operator End //////////////////////////////////////////////////////

void String::print(ostream &out) const {
	out << buf;
}

void String::read(istream &in) {
	//char temp[1024];
	//in >> temp;

//	delete[] buf;
	//buf = strdup(temp);	
}


// Helpers /////////////////////////////////////////////////////////////////////
int String::strlen(const char *s) {
	int i = 0;
	for(; s[i] != '\0'; ++i) {}

	return i;
}

char *strdup(const char *src) {
	size_t length = strlen(src) + 1;
	char * new_string {new char[length]};
	strcpy(new_string, src);
	return new_string;
}

char *String::strcpy(char *dest, const char *src) {
	int i = 0;
	for(; src[i] != '\0'; ++i) {
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return dest;
}

char *String::strncpy(char *dest, const char *src, int n) {
	int i = 0;
	for(; (i < n) && (src[i] != '\0'); ++i) {
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return dest;
}

char *String::strcat(char *dest, const char *src) {
	int source_length = strlen(src);
	int dest_index = strlen(dest);
	int src_index = 0;
	for(; src_index < source_length; ++dest_index, ++src_index) {
		dest[dest_index] = src[src_index];
	}
	dest[dest_index] = '\0';

	return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
	int source_length = strlen(src);
	int dest_index = strlen(dest);
	int src_index = 0;
	for(; (src_index < source_length) && (src_index < n); ++dest_index, ++src_index) {
		dest[dest_index] = src[src_index];
	}
	dest[dest_index] = '\0';

	return dest;
}

int String::strcmp(const char *left, const char *right) {
	int difference;
	for(int i = 0; (left[i] != '\0') || (right[i] != '\0'); ++i) {
		difference = left[i] - right[i];
		if (difference != 0) {
			return difference;
		}
	}
	return 0;
}

int String::strncmp(const char *left, const char *right, int n) {
	int difference;
	for(int i = 0; ((left[i] != '\0') || (right[i] != '\0')) && (i < n); ++i) {
		difference = left[i] - right[i];
		if (difference != 0) {
			return difference;
		}
	}
	return 0;
}

void String::reverse_cpy(char *dest, const char *src) {
	int dest_index = strlen(src) - 1;
	int src_index = 0;
	for(; src[src_index] != '\0'; ++src_index, --dest_index) {
		dest[dest_index] = src[src_index];
	}
	dest[src_index] = '\0';
}

const char *String::strchr(const char *str, char c) {
	// must include null terminator, so strange setup required
	for(int i = 0; ; ++i) {
		if (str[i] == c) {
			return &str[i];
		}

		if (str[i] == '\0') {
			return nullptr;
		}
	}
}

const char *String::strstr(const char *haystack, const char *needle) {
	if (needle[0] == '\0') {
		return haystack;
	}

	for(int i = 0; haystack[i] != '\0'; ++i) {
		int j = 0;

		if (haystack[i] == needle[j]) {
			for(; haystack[i + j] == needle[j] && haystack[i + j] != '\0'; ++j) {}
			if (needle[j] == '\0') {
				return &haystack[i];
			}
		}
	}

	return nullptr;
}

////////////////////////////////////////////////////////////////////////////
