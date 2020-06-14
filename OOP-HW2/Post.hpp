#pragma once

#include "string.hpp"

enum class PostType {
    TEXT,
    IMAGE,
    LINK
};

class Post {
public:
    Post(vector<string> args, PostType type);
    Post();
    int get_id();
    string get_html();
private:
    static int id_counter;
    int id;
    vector<string> content;
    PostType type;
};

