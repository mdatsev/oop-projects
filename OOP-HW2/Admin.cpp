#include "Admin.hpp"

void Admin::add_user(const string& name, int age) {
    app.add_user<User>(name, age);
}

void Admin::add_mod(const string& name, int age) {
    app.add_user<Mod>(name, age);
}

void Admin::remove_user(const string& name) {
    app.remove_user(name);
}

string Admin::get_role_text() {
    return "Administrator";
}