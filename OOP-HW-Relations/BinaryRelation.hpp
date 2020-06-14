#pragma once

#include <iostream>
#include "set.hpp"
#include "string.hpp"

template <typename T, typename U>
struct Pair {
    T left;
    U right;
    bool operator==(const Pair<T, U>& rhs) const {
        return left == rhs.left && right == rhs.right;
    }
    bool operator<(const Pair<T, U>& rhs) const {
        return left == rhs.left ? right < rhs.right : left < rhs.left;
    }
    friend std::ostream& operator<<(std::ostream& output, const Pair<T, U>& p) {
        return output << "( " << p.left << " " << p.right << " )";
    }

    friend std::istream& operator>>(std::istream& input, Pair<T, U>& p) {
        string dummy;
        input >> dummy; // (
        input >> p.left;
        input >> p.right;
        input >> dummy; // )
        return input;
    }
};

template <typename T, typename U>
class BinaryRelation {
    template<typename A, typename B> using R = BinaryRelation<A, B>;
    set<Pair<T, U>> pairs;

public:

    const set<Pair<T, U>>& get_pairs() const {
        return pairs;
    }

    R<T, U>& add_pair(const Pair<T, U>& p) {
        pairs.add(p);
        return *this;
    }

    R<T, U>& add_pair(T left, U right) {
        add_pair({ left, right });
        return *this;
    }

    bool contains(const Pair<T, U>& p) const {
        return pairs.contains(p);
    }

    U& get_value(const T& arg) {
        for (auto& [t, u] : pairs) {
            if (t == arg) {
                return u;
            }
        }
    }

    set<T> dom() {
        set<T> result;

        for (auto& [t, _] : pairs) {
            result.add(t);
        }

        return result;
    }

    set<U> ran() {
        set<U> result;

        for (auto& [_, u] : pairs) {
            result.add(u);
        }

        return result;
    }

    bool function() {
        auto domain = dom();
        for (auto& t : domain) {
            if (operator[](t).size() > 1) {
                return false;
            }
        }
        return true;
    }

    bool injection() {
        auto range = ran();
        for (auto& u : range) {
            if (operator()(u).size() != 1) {
                return false;
            }
        }
        return true;
    }

    bool operator()(T t, U u) const {
        return contains({ t, u });
    }

    R<U, T> operator!() const {
        auto result = R<U, T>();

        for (auto& [t, u] : pairs) {
            result.add_pair(u, t);
        }

        return result;
    }

    R<T, U> operator+(const R<T, U>& rhs) const {
        auto result = rhs;

        for (auto& p : pairs) {
            result.add_pair(p);
        }

        return result;
    }

    R<T, U> operator^(const R<T, U>& rhs) const {
        R<T, U> result;

        for (auto& p : pairs) {
            if (rhs.contains(p)) {
                result.add_pair(p);
            }
        }

        return result;
    }

    set<U> operator[](const T& value) const {
        set<U> result;

        for (auto& [t, u] : pairs) {
            if (t == value) {
                result.add(u);
            }
        }

        return result;
    }

    set<T> operator()(const U& value) const {
        set<T> result;

        for (auto& [t, u] : pairs) {
            if (u == value) {
                result.add(t);
            }
        }

        return result;
    }

    template<typename V>
    friend R<T, V> operator*(const R<T, U>& r1, const R<U, V>& r2) {
        R<T, V> result;

        for (auto& [t, u1] : r1.pairs) {
            for (auto& [u2, v] : r2.get_pairs()) {
                if (u1 == u2) {
                    result.add_pair(t, v);
                }
            }
        }

        return result;
    }

    R<T, U>& operator*=(const R<U, U>& rhs) {
        return *this = *this * rhs;
    }

    R<T, U>& operator^=(const R<T, U>& rhs) {
        return *this = *this ^ rhs;
    }

    R<T, U>& operator+=(const R<T, U>& rhs) {
        return *this = *this + rhs;
    }
    
    bool operator==(const R<T, U>& rhs) const {
        return pairs == rhs.pairs;
    }

    friend std::ostream& operator<<(std::ostream& output, const R<T, U>& r) {
        return output << r.pairs;
    }

    friend std::istream& operator>>(std::istream& input, R<T, U>& r) {
        return input >> r.pairs;
    }
};

