#pragma once

#include "vector.hpp"
#include "string.hpp"

template <typename T>
class set {
    vector<T> elements;

public:
    bool contains(T el) const {
        return elements.contains(el);
    }

    bool add(T el) {
        if (contains(el)) {
            return false;
        }
        elements.push_back(el);
        return true;
    }

    bool remove(T el) {
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i] == el) {
                elements.remove_at(i);
                return true;
            }
        }
        return false;
    }

    int size() const {
        return elements.size();
    }

    auto begin() const { return elements.begin(); }
    auto end() const { return elements.end(); }

    friend std::ostream& operator<<(std::ostream& output, const set<T>& s) {
        output << s.size() << " ";
        output << "{ ";
        for (auto e : s.elements) {
            output << e << " ";
        }
        output << "}";
        return output;
    }

    friend std::istream& operator>>(std::istream& input, set<T>& s) {
        s = set();
        int size;
        input >> size;
        string dummy;
        input >> dummy; // {
        for (int i = 0; i < size; i++) {
            T t;
            input >> t;
            //std::cout << i << t << size <<std::endl;
            s.add(t);
        }
        input >> dummy; // }
        return input;
    }

    bool operator==(const set<T>& rhs) const {

        if (size() != rhs.size()) {
            return false;
        }

        auto lhs_sorted = elements.sorted();
        auto rhs_sorted = rhs.elements.sorted();

        for (int i = 0; i < size(); i++) {
            if (!(lhs_sorted[i] == rhs_sorted[i])) {
                return false;
            }
        }

        return true;
    }
};
