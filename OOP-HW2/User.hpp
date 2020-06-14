#pragma once

#include "string.hpp"
#include "App.hpp"
#include "Post.hpp"
class App;
class User
{
public:
    User(const string& name, int age, App& app);
    const string& get_name();
    int get_age();
    const vector<Post>& get_posts();
    void set_blocked(bool value);
    bool is_blocked();
    void rename(const string& name);
    virtual void add_user(const string& name, int age);
    virtual void add_mod(const string& name, int age);
    virtual void remove_user(const string& name);
    virtual void set_blocked(const string& name, bool value);
    virtual void remove_post(int id);
    virtual string get_role_text();
    void add_post(const vector<string> args, PostType type);
protected:
    App& app;
private:
    string name;
    const int age;
    bool blocked;
    vector<Post> posts;
};

