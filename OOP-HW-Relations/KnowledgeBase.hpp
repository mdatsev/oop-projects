#pragma once

#include "BinaryRelation.hpp"

template <typename T, typename U>
class KnowledgeBase {
    template<typename A, typename B> using R = BinaryRelation<A, B>;
    template<typename A, typename B> using KB = KnowledgeBase<A, B>;

    R<string, R<T, U>> relations;

public:
    R<T, U>& operator()(string name) {
        if (relations[name].size() == 0) {
            relations.add_pair(name, {});
        }

        return relations.get_value(name);
    }
    

    set<string> dom() {
        return relations.dom();
    }

    set<R<T, U>> ran() {
        return relations.ran();
    }

    bool function() {
        return relations.function();
    }

    bool injection() {
        return relations.injection();
    }

    KB<U, T> operator!() const {
        KB<U, T> result;
        for (auto& [name, rel] : relations.get_pairs()) {
            result(name) = !rel;
        }
        return result;
    }

    KB<T, U> operator+(const KB<T, U>& rhs) const {
        KB<T, U> result;
        result.relations = relations + rhs.relations;
        return result;
    }

    KB<T, U> operator^(const KB<T, U>& rhs) const {
        KB<T, U> result;
        result.relations = relations ^ rhs.relations;
        return result;
    }

    set<R<T, U>> operator[](const string& value) const {
        return relations[value];
    }

    template<typename V>
    friend KB<T, V> operator*(const KB<T, U>& r1, const KB<U, V>& r2) {
        KB<T, V> result;
        result.relations = r1.relations + r2.relations;
        return result;
    }

    KB<T, U>& operator*=(const KB<U, U>& rhs) {
        relations = relations * rhs.relations;
        return *this;
    }

    KB<T, U>& operator^=(const KB<T, U>& rhs) {
        relations = relations ^ rhs.relations;
        return *this;
    }

    KB<T, U>& operator+=(const KB<T, U>& rhs) {
        relations = relations + rhs.relations;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& output, const KB<T, U>& kb) {
        return output << kb.relations;
    }

    friend std::istream& operator>>(std::istream& input, KB<T, U>& kb) {
        return input >> kb.relations;
    }

};