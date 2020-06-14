#include "App.hpp"

#include <memory>
#include <fstream>

#include "User.hpp"
#include "Mod.hpp"
#include "Admin.hpp"

App::App()
{
}

void App::run()
{
    std::cout << "Enter admin username:";
    string admin_username;
    std::cin >> admin_username;

    std::cout << "Enter admin age:";
    string admin_age;
    std::cin >> admin_age;

    add_user<Admin>(admin_username, admin_age);

    while (1) {
        std::cout << "$: ";
        string command;
        command.readline(std::cin);
        auto args = command.split();

        if (args.is_singleton("quit")) {
            break;
        } else if (args.is_singleton("info")) {
            print_info();
        } else if (args.size() < 3){
            std::cout << "Action usage: <actor> <action> <subject> [<parameters>]" << std::endl;
        } else {
            User* actor = find_user(args[0]);

            if (!actor) {
                std::cout << "No such actor: " << args[0] << std::endl;
                continue;
            }

            string& action = args[1];
            if (action == "add_user") {
                if (args.size() < 4) {
                    std::cout << "You need specify age!" << std::endl;
                    continue;
                }
                actor->add_user(args[2], to_int(args[3]));
            } else if (action == "add_moderator") {
                if (args.size() < 4) {
                    std::cout << "You need specify age!" << std::endl;
                    continue;
                }
                actor->add_mod(args[2], to_int(args[3]));
            } else if (action == "remove_user") {
                actor->remove_user(args[2]);
            } else if (action == "block") {
                actor->set_blocked(args[2], true);
            } else if (action == "unblock") {
                actor->set_blocked(args[2], false);
            } else if (action == "post") {
                PostType type;
                if (args[2] == "[image]") {
                    type = PostType::IMAGE;
                } else if (args[2] == "[url]") {
                    type = PostType::LINK;
                } else if (args[2] == "[text]") {
                    type = PostType::TEXT;
                } else {
                    std::cout << "Invalid post type!" << std::endl;
                    continue;
                }
                actor->add_post(args.slice(3), type);
            } else if (action == "remove_post") {
                actor->remove_post(to_int(args[2]));
            } else if (action == "view_post") {
                view_post(to_int(args[2]));
            } else if (action == "view_all_posts") {
                view_all_posts(args[2]);
            } else if (action == "rename") {
                actor->rename(args[2]);
            } else {
                std::cout << "Unknown command!" << std::endl;
            }
        }

    }
}

User* App::find_user(const string& name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->get_name() == name) {
            return users[i].get();
        }
    }
    return nullptr;
}

void App::remove_user(const string& name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->get_name() == name) {
            users.remove_at(i);
            std::cout << name << " removed." << std::endl;
            return;
        }
    }
    std::cout << "User not found!" << std::endl;
}

void App::set_blocked(const string& name, bool value) {
    User* user = find_user(name);
    
    if (!user) {
        std::cout << "User not found!" << std::endl;
        return;
    }

    user->set_blocked(value);
}

void App::remove_post(int id) {
    for (int i = 0; i < users.size(); i++) {
        auto posts = users[i]->get_posts();
        for (int j = 0; j < posts.size(); j++) {
            if (posts[i].get_id() == id) {
                posts.remove_at(i);
                std::cout << "Post " << id << " removed." << std::endl;
            }
        }
    }
    std::cout << "No such post." << std::endl;
}

void App::view_post(int id) {
    for (int i = 0; i < users.size(); i++) {
        auto posts = users[i]->get_posts();
        for (int i = 0; i < posts.size(); i++) {
            if (posts[i].get_id() == id) {
                std::fstream file("output.html", std::ios::out | std::ios::trunc);
                file << posts[i].get_html();
                std::cout << "View post in output.html" << std::endl;
                return;
            }
        }
    }
    std::cout << "No such post!" << std::endl;
}


void App::view_all_posts(const string& name) {
    User* user = find_user(name);

    if (!user) {
        std::cout << "User not found!" << std::endl;
        return;
    }

    std::fstream file("output.html", std::ios::out | std::ios::trunc);
    auto posts = user->get_posts();
    for (int i = 0; i < posts.size(); i++) {
        file << posts[i].get_html();
    }
    std::cout << "View posts in output.html" << std::endl;
}

void App::print_info() {
    std::cout << "There are " << users.size() << " users:" << std::endl;

    for (int i = 0; i < users.size(); i++) {
        auto& user = *users[i].get();
        std::cout << user.get_name() << " - " << user.get_role_text() << ", " << user.get_posts().size() << " posts." << std::endl;
    }

    int nBlocked = 0;
    int youngest_age = users[0]->get_age();
    int oldest_age = users[0]->get_age();
    string youngest;
    string oldest;
    for (int i = 0; i < users.size(); i++) {
        auto& user = *users[i].get();

        nBlocked += user.is_blocked();

        if (user.get_age() <= youngest_age) {
            youngest = user.get_name();
            youngest_age = user.get_age();
        }

        if (user.get_age() >= oldest_age) {
            oldest = user.get_name();
            oldest_age = user.get_age();
        }
    }
    if (nBlocked) {
        std::cout << "There are " << nBlocked << " users." << std::endl;
    } else {
        std::cout << "There aren't any blocked users." << std::endl;
    }

    std::cout << "oldest " << oldest << " " << oldest_age << std::endl;
    std::cout << "youngest " << youngest << " " << youngest_age << std::endl;
};