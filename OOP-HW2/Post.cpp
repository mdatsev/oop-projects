#include "Post.hpp"

Post::Post() {};

Post::Post(vector<string> content, PostType type) : content(content), type(type) {
    id = id_counter++;
    std::cout << "Post " << id << " created." << std::endl;
};

int Post::get_id() {
    return id;
}

string Post::get_html() {
    if (type == PostType::IMAGE) {
        return "<img src=\"" + content[0] + "\">";
    } else if (type == PostType::LINK) {
        string link_text = content.size() == 1 ? content[0] : join(content.slice(1), ' ');
        return "<a href=\"" + content[0] + "\">" + link_text + "</a>";
    } else if (type == PostType::TEXT) {
        return "<p>" + join(content, ' ') + "</p>";
    }
}

int Post::id_counter = 0;