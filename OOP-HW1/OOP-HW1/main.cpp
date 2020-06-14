#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <functional>
#include <utility>
#include <iomanip>

#include "vector.hpp"
#include "string.hpp"
#include "Challenge.hpp"
#include "User.hpp"

int main() {

    vector<User> users;
    auto user_is_registered = [&](string name) { return users.contains([&](auto u) { return u.name == name; }); };

    vector<Challenge> challs;

    while (1) {
        std::cout << ">";
        string command;
        command.readline(std::cin);
        auto args = command.split();
        if (args[0] == "registration") {
            User u(args[1]);
            if (args.size() > 3) {
                u.age = to_int(args[2]);
                u.email = args[3];
            } else {
                if (args[2].contains('@')) {
                    u.email = args[2];
                } else {
                    u.age = to_int(args[2]);
                }
            }

            if (u.age > 90) {
                std::cout << "Registration Fail. You are too old for this App.\n";
                continue;
            }

            if (u.email.size() > 100) {
                std::cout << "Registration Fail. You have too long email for this App.\n";
                continue;
            }

            if (u.email) {
                std::cout << "Registration Successful. Please check your email.\n";
            } else {
                std::cout << "Registration Successful.\n";
            }

            users.append(u);
        } else if (args[0] == "challenge") {
            string name = args[1];
            string tag = args[2];

            bool all_registered = user_is_registered(name);
            for (int i = 3; i < args.size() && all_registered; i++) {
                if (!user_is_registered(args[i])) {
                    all_registered = false;
                }
            }

            if (!all_registered) {
                std::cout << "Sorry, some of the users may not be registered!\n";
            }

            if (tag[0] != '#' || tag.size() > 31) {
                std::cout << "Sorry! Invalid tag of the challenge.\n";
            }

            int found = challs.find([&](auto c) { return c.tag == tag; });

            if (found < 0) {
                challs.append({ tag });
            } else {
                challs[found].challenge();
            }
        } else if (args[0] == "finish") {
            string tag = args[1];
            int user_id = to_int(args[2]);
            float score = to_float(args[3]);

            if (!users.contains([&](auto u) { return u.id == user_id; })) {
                std::cout << "The given id isn’t valid. The user with this id do not exist.\n";
            }

            if (score < -5 || score > 10) {
                std::cout << "Sorry. Invalid rating! The challenge is not completed, yet.\n";
            }

            int found = challs.find([&](auto c) { return c.tag == tag; });
            if (found < 0) {
                std::cout << "Challenge not challenged by anyone yet.\n";
            } else {
                std::cout << "Well done! May the challenge be with you!\n";
                challs[found].finish(score);
            }
        } else if (args[0] == "profile_info") {
            string name = args[1];

            std::cout << "Searching for users...\n";
            bool found = false;
            for (int i = 0, j = 1; i < users.size(); i++) {
                auto& u = users[i];
                if (u.name == name) {
                    std::cout << j++ << ')\n';
                    std::cout << "Name: " << u.name << '\n';
                    if (u.age < 0) {
                        std::cout << "Age: Unknown\n";
                    } else {
                        std::cout << "Age: " << u.age << '\n';
                    }

                    if (u.email.size() > 0) {
                        std::cout << "Email: " << u.email << '\n';
                    } else {
                        std::cout << "Email: Unknown\n";
                    }
                    std::cout << "Id: " << u.id << '\n';

                }
            }

        } else if (args[0] == "list_by") {
            std::cout << "Tag            Rating         Status         Total          Done\n";
            if (args[1] == "newest") {
                for (int i = challs.size() - 1; i >= 0; i--) {
                    std::cout << challs[i] << '\n';
                }
            } else if (args[1] == "oldest") {
                for (int i = 0; i < challs.size(); i++) {
                    std::cout << challs[i] << '\n';
                }
            } else if (args[1] == "most_popular") {
                auto sorted = challs.sorted([](auto c1, auto c2) { return c2.times_challenged - c1.times_challenged; });
                for (int i = 0; i < sorted.size(); i++) {
                    std::cout << sorted[i] << '\n';
                }
            } else {
                std::cout << "Invalid sort\n";
            }
        } else {
            std::cout << "unknown command\n";
        }
    }
    return 0;
}