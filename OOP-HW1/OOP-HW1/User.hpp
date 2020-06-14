#pragma once

#include "string.hpp"

class User
{
public:
    static int id_counter;
    string name;
    int age;
    string email;
    int id;
    User(string name = {}, int age = -1, string email = {});
};