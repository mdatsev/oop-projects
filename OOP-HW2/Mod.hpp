#pragma once

#include "User.hpp"

class Mod :
    public User
{
    using User::User;
    void set_blocked(const string& user, bool value) override;
    void remove_post(int id) override;
    string get_role_text() override;
};

