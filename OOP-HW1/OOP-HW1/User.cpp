#include "User.hpp"

int User::id_counter = 0;

User::User(string name, int age, string email)
    : name(name), age(age), email(email), id{ id_counter++ } {

}
