#include "User.hpp"

#include <iostream>

#include "string.hpp"

User::User(const string& name, int age, App& app) : name(name), age(age), app(app), blocked(false) {

}

const string& User::get_name() {
    return name;
}

int User::get_age() {
    return age;
}

const vector<Post>& User::get_posts() {
    return posts;
}

string User::get_role_text() {
    return "User";
}

void User::add_user(const string& name, int age)
{
    std::cout << "You don't have permission to add users!" << std::endl;
}

void User::add_mod(const string& name, int age) {
    std::cout << "You don't have permission to add users!" << std::endl;
}

void User::remove_user(const string& name) {
    std::cout << "You don't have permission to remove users!" << std::endl;
}

void User::set_blocked(bool value) {
    blocked = value;
    std::cout << name << (value ? " blocked" : " unblocked") << std::endl;
}

bool User::is_blocked() {
    return blocked;
}

void User::rename(const string& new_name) {
    std::cout << "User " << name << " is now known as " << new_name << "." << std::endl;
    name = new_name;
}

void User::set_blocked(const string& user, bool value) {
    app.set_blocked(user, value);
}

void User::add_post(const vector<string> args, PostType type) {
    if (blocked) {
        std::cout << "Post not created - user blocked!" << std::endl;
        return;
    }

    posts.push_back(Post(args, type));
}

void User::remove_post(int id) {
    for (int i = 0; i < posts.size(); i++) {
        if (posts[i].get_id() == id) {
            posts.remove_at(i);
            std::cout << "Post " << id << " removed." << std::endl;
            return;
        }
    }
    std::cout << "Post not removed - you haven't posted a post with this id!" << std::endl;
}