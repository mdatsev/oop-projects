#pragma once

#include "Mod.hpp"

class Admin :
    public Mod
{
    using Mod::Mod;
    virtual void add_user(const string& name, int age) override;
    virtual void add_mod(const string& name, int age) override;
    virtual void remove_user(const string& name) override;
    string get_role_text() override;
};

