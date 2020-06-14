#pragma once

#include <functional>

template <typename T>
class vector
{
    T* data_;
    int size_;

public:
    vector() : data_(nullptr), size_(0) {

    }

    vector(const vector& v) : vector() {
        *this = v;
    }

    vector& operator=(const vector& v) {
        delete[] data_;
        size_ = v.size_;
        data_ = new T[v.size_];

        for (int i = 0; i < size_; i++) {
            data_[i] = v[i];
        }
        return *this;
    }

    ~vector() {
        delete[] data_;
    }

    void push_back(T value) {
        T* new_data = new T[++size_];
        for (int i = 0; i < size_ - 1; i++) {
            new_data[i] = std::move(data_[i]);
        }
        new_data[size_ - 1] = std::move(value);
        delete[] data_;
        data_ = new_data;
    }

    bool contains(T value) const {
        return contains([&](auto el) { return el == value; });
    }

    bool contains(std::function<bool(T)> predicate) const {
        return find(predicate) != -1;
    }

    int find(std::function<bool(T)> predicate) const {
        for (int i = 0; i < size_; i++) {
            if (predicate(data_[i])) {
                return i;
            }
        }
        return -1;
    }

    void remove_at(int idx) {
        for (int i = idx; i < size_ - 1; i++) {
            data_[i] = std::move(data_[i+ 1]);
        }
        size_--;
    }

    vector<T> slice(int start) {
        return slice(start, size_);
    }

    vector<T> slice(int start, int end) {
        vector<T> result;
        for (int i = start; i < end; i++) {
            result.push_back(data_[i]);
        }
        return result;
    }

    void sort(std::function<int(T, T)> comp) {
        bool sorted = false;
        while (!sorted) {
            sorted = true;
            for (int i = 1; i < size_; i++) {
                if (comp(data_[i], data_[i - 1]) < 0) {
                    std::swap(data_[i], data_[i - 1]);
                    sorted = false;
                }
            }
        }
    }

    vector<T> sorted(std::function<int(T, T)> comp) const {
        vector<T> result = *this;
        result.sort(comp);
        return result;
    }

    int size() const {
        return size_;
    }

    T* data() const {
        return data_;
    }

    const T& operator[](int index) const {
        return data_[index];
    }

    T& operator[](int index) {
        return data_[index];
    }

    bool is_singleton(const T& value) {
        return size() == 1 && data_[0] == value;
    }
};
