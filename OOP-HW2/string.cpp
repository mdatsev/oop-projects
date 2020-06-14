#include "string.hpp"

string::string() {
    data.push_back('\0');
}

string::string(const char* str) : string() {
    while (*str != '\0') {
        append(*str);
        str++;
    }
}

void string::append(char c) {
    data[data.size() - 1] = c;
    data.push_back('\0');
}

int string::size() const {
    return data.size() - 1;
}

vector<string> string::split() const {
    vector<string> words;
    string current;
    bool in_word = false;
    for (int i = 0; i < size(); i++) {
        if (in_word) {
            if (isspace(data[i])) {
                words.push_back(std::move(current));
                current = {};
                in_word = false;
            } else {
                current.append(data[i]);
            }
        } else {
            if (!isspace(data[i])) {
                in_word = true;
                current.append(data[i]);
            }
        }
    }
    if (in_word) {
        words.push_back(std::move(current));
    }
    return words;
}

void string::readline(std::istream& input) {
    char c;
    input >> std::noskipws;
    while (input.get(c)) {
        if (c == '\n') {
            break;
        }
        append(c);
    }
}

bool string::contains(char c) const {
    return data.contains(c);
}

bool string::contains(std::function<bool(char)> predicate) const {
    return data.contains(predicate);
}

const char* string::c_str() const {
    return data.data();
}

const char& string::operator[](int index) const {
    return data[index];
}

char& string::operator[](int index) {
    return data[index];
}

bool string::operator==(const char* cstr) const {
    if (strlen(cstr) != size()) {
        return false;
    }
    for (int i = 0; i < size(); i++) {
        if (cstr[i] != data[i]) {
            return false;
        }
    }
    return true;
}

bool string::operator==(string rhs) const {
    if (rhs.size() != size()) {
        return false;
    }
    for (int i = 0; i < size(); i++) {
        if (rhs[i] != data[i]) {
            return false;
        }
    }
    return true;
}

string::operator bool() const {
    return size() > 0;
}

std::istream& operator>>(std::istream& input, string& s) {
    char c;
    input >> std::noskipws;
    while (input.get(c)) {
        if (isspace(c)) {
            break;
        }
        s.append(c);
    }
    return input;
}

std::ostream& operator<<(std::ostream& output, const string& s) {
    output << s.c_str();
    return output;
}

int to_int(string s) {
    return std::atoi(s.c_str());
}

float to_float(string s) {
    return std::atof(s.c_str());
}

string operator+(const string& lhs, const string& rhs) {
    string result(lhs);
    for (int i = 0; i < rhs.size(); i++) {
        result.append(rhs[i]);
    }
    return result;
}

string operator+(const char* lhs, const string& rhs) {
    return string(lhs) + rhs;
}
string operator+(const string& lhs, const char* rhs) {
    return lhs + string(rhs);
}

string join(const vector<string>& arr, char delim) {
    string result;

    for (int i = 0; i < arr.size(); i++) {
        if (i > 0) {
            result.append(delim);
        }
        result = result + arr[i];
    }

    return result;
}