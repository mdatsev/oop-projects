#include "Mod.hpp"

void Mod::set_blocked(const string& user, bool value) {
    app.set_blocked(user, value);
}

void Mod::remove_post(int id) {
    app.remove_post(id);
}

string Mod::get_role_text() {
    return "Moderator";
}