#pragma once

#include <memory>
#include <iostream>

#include "vector.hpp"
#include "string.hpp"
#include "User.hpp"
#include "Post.hpp"

class User;
class App
{
public:
    App();
    void run();
    void remove_user(const string& name);
    void set_blocked(const string& name, bool value);
    void remove_post(int id);

    template <typename T>
    void add_user(const string& name, int age) {
        if (find_user(name)) {
            std::cout << "Username is taken!" << std::endl;
            return;
        }
        users.push_back(std::make_unique<T>(name, age, *this));
        std::cout << name << " created." << std::endl;
    }
private:
    vector<std::unique_ptr<User>> users;
    User* find_user(const string& name);
    void view_post(int id);
    void view_all_posts(const string& id);
    void print_info();
};

