#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "mystring.hpp"
#include <cstring>

TEST_CASE("Len") {
    REQUIRE(MyString().len() == 0);
    REQUIRE(MyString("1").len() == 1);
    REQUIRE(MyString("12345").len() == 5);
    REQUIRE(MyString("abcdef").len() == 6);
}

TEST_CASE("Set") {
    MyString string("0123456789");
    string.set(0, 'a');
    REQUIRE(strcmp(string.c_str(), "a123456789") == 0);

    string.set(1, 'b');
    string.set(2, 'c');
    string.set(3, 'd');
    REQUIRE(strcmp(string.c_str(), "abcd456789") == 0);
}

TEST_CASE("Get") {
    MyString string("0123456789");
    REQUIRE(string.get(0) == '0');
    REQUIRE(string.get(1) == '1');
    REQUIRE(string.get(3) == '3');
}

TEST_CASE("c_str") {
    REQUIRE(strcmp(MyString().c_str(), "") == 0);
    REQUIRE(strcmp(MyString("Hello").c_str(), "Hello") == 0);
}

TEST_CASE("Reverse") {
    MyString empty;
    MyString string("12345");

    empty.reverse();
    string.reverse();

    REQUIRE(strcmp(empty.c_str(), "") == 0);
    REQUIRE(strcmp(string.c_str(), "54321") == 0);
}

TEST_CASE("Find First") {
    SECTION("Characters") {
        REQUIRE(MyString().find_first('a') == -1);
        REQUIRE(MyString("1").find_first('1') == 0);
        REQUIRE(MyString("111").find_first('1') == 0);
        REQUIRE(MyString("123345").find_first('3') == 2);
    }
    SECTION("Strings") {
        REQUIRE(MyString().find_first("1234123") == -1);
        REQUIRE(MyString("abcdefg").find_first("123") == -1);
        REQUIRE(MyString("abcde").find_first("abc") == 0);
        REQUIRE(MyString("abcdeabc").find_first("abc") == 0);
        REQUIRE(MyString("123123123").find_first("123") == 0);
        REQUIRE(MyString("123456789").find_first("789") == 6);
    }
}

TEST_CASE("Find Last") {
    SECTION("Characters") {
        REQUIRE(MyString().find_last('a') == -1);
        REQUIRE(MyString("1").find_last('1') == 0);
        REQUIRE(MyString("111").find_last('1') == 2);
        REQUIRE(MyString("123345").find_last('3') == 3);
    }
    SECTION("Strings") {
        REQUIRE(MyString().find_last("1234123") == -1);
        REQUIRE(MyString("abcdefg").find_last("123") == -1);
        REQUIRE(MyString("abcde").find_last("abc") == 0);
        REQUIRE(MyString("abcdeabc").find_last("abc") == 5);
        REQUIRE(MyString("123123123").find_last("123") == 6);
        REQUIRE(MyString("123456789").find_last("789") == 6);
    }
}

TEST_CASE("Compare") {
    REQUIRE(MyString("B").compare("B") == 0);
    REQUIRE(MyString("B").compare("A") == -1);
    REQUIRE(MyString("B").compare("C") == 1);
    
    REQUIRE(MyString("BBB").compare("BBA") == -1);
    REQUIRE(MyString("BBB").compare("BBAB") == -1);
    REQUIRE(MyString("BBB").compare("BBCB") == 1);
}

TEST_CASE("Append") {
    MyString string;
    SECTION("A single character") {
        string.append('a');
        REQUIRE(strcmp(string.c_str(), "a") == 0);
        string.append('1');
        REQUIRE(strcmp(string.c_str(), "a1") == 0);
        string.append('\n');
        REQUIRE(strcmp(string.c_str(), "a1\n") == 0);
    }
    SECTION("A string") {
        string.append("hello");
        REQUIRE(strcmp(string.c_str(), "a1\nhello") == 0);
        string.append("world");
        REQUIRE(strcmp(string.c_str(), "a1\nhelloworld") == 0);
    }
}
