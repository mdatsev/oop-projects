#include "string.hpp"

string::string() {
    data.append('\0');
}

void string::append(char c) {
    data[data.size() - 1] = c;
    data.append('\0');
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
                words.append(current);
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
        words.append(current);
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

std::ostream& operator<<(std::ostream& output, string& s) {
    output << s.c_str();
    return output;
}

int to_int(string s) {
    return std::atoi(s.c_str());
}

float to_float(string s) {
    return std::atof(s.c_str());
}