#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"


TEST(StringFunction, strdup) {
    char big_buf[2000] {};
	for (int i = 0; i < 1999; ++i) {
		big_buf[i] = 'e';
	}
	char * big_string {String::strdup(big_buf)};
	EXPECT_EQ(big_string[1998], 'e');

	char small_buf[] {"Hello"};
	char * other_buf {String::strdup(small_buf)};
	small_buf[0] = 'Y';
	
	EXPECT_STREQ(other_buf, "Hello");
	delete[] big_string;
	delete[] other_buf;
}

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncpy) {
    char result[10];

	EXPECT_EQ(String::strncpy(result, "012345", 2), result);
	EXPECT_STREQ(result, "01");

	String::strncpy(result, "012345", 0);
	EXPECT_STREQ(result, "");

	String::strncpy(result, "012345", 300);
	EXPECT_STREQ(result, "012345");
}

TEST(StringFunction, strcat) {
    char result[80] {""};

	String::strcat(result, "");
	EXPECT_STREQ(result, "");

	String::strcat(result, "Hello ");
	String::strcat(result, "World!");
	EXPECT_STREQ(result, "Hello World!");
}

TEST(StringFunction, strncat) {
	char result[80]	{""};

	String::strncat(result, "012345", 2);
	EXPECT_STREQ(result, "01");

	String::strncat(result, "2345", 30);
	EXPECT_STREQ(result, "012345");

	String::strncat(result, "Hello World!", 0);
	EXPECT_STREQ(result, "012345");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("", ""), 0);
	EXPECT_EQ(String::strcmp("a", "A"), 'a' - 'A');
	EXPECT_EQ(String::strcmp("A", "a"), 'A' - 'a');

	EXPECT_EQ(String::strcmp("lemonA", "lemonB"), -1);
	EXPECT_EQ(String::strcmp("A ", "A   Z"), -32);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("Elephant", "Squid", 0), 0);
	EXPECT_EQ(String::strncmp("123 hello", "123 world", 5), -15);
	EXPECT_EQ(String::strncmp("R2D2", "R2xx", 2), 0);

	EXPECT_EQ(String::strncmp("aA", "aZamala", 30), -25);
	EXPECT_EQ(String::strncmp("", "", 5), 0);
}

TEST(StringFunction, reverse_cpy) {
	char result[80] {};
	String::reverse_cpy(result, "hello");
    EXPECT_STREQ(result, "olleh");

	String::reverse_cpy(result, "");
	EXPECT_STREQ(result, "");

	String::reverse_cpy(result, "a,");
	EXPECT_STREQ(result, ",a");
}

TEST(StringFunction, strchr) {
	char empty_string[] {""};
    EXPECT_EQ(String::strchr(empty_string, '\0'), &empty_string[0]);

	char hello[] {"Hello World!!!"};
	EXPECT_EQ(String::strchr(hello, '!'), &hello[11]);

	char randomstr[] {"lemon"};
	EXPECT_EQ(String::strchr(randomstr, 'a'), nullptr);
}

TEST(StringFunction, strstr) {
    char empty_string[] {""};
    EXPECT_EQ(String::strstr(empty_string, ""), empty_string);

	char uhh[] {"uhh"};
	EXPECT_EQ(String::strstr(uhh, "uh"), &uhh[0]);

	char hello[] {"Hello World!!!"};
	EXPECT_EQ(String::strstr(hello, "World!"), &hello[6]);

	char randomstr[] {" aAa a a a a a ab hmmm aaa"};
	EXPECT_EQ(String::strstr(randomstr, " aa"), &randomstr[22]);

	char scaryString[] {"aabaaban"};
	EXPECT_EQ(String::strstr(scaryString, "aban"), &scaryString[4]);
}
