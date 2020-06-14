#pragma once

#include <iostream>
#include <functional>

#include "vector.hpp"

class string
{
    vector<char> data;
public:

    string();

    void append(char c);

    int size() const;

    const char& operator[](int index) const;

    char& operator[](int index);

    vector<string> split() const;

    void readline(std::istream& input);

    bool contains(char c) const;

    bool contains(std::function<bool(char)> predicate) const;

    const char* c_str() const;

    bool operator==(const char* cstr) const;

    bool operator==(string rhs) const;

    operator bool() const;
};

std::istream& operator>>(std::istream& input, string& s);
std::ostream& operator<<(std::ostream& output, string& s);

int to_int(string s);

float to_float(string s);