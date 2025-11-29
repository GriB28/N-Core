#include "void.h"

#include <iostream>


game::object::Void::Void(const string &chapter_id, const bool is_kill_zone) : Object(chapter_id) {
    this->is_kill_zone = is_kill_zone;
    reset_sprite("void", "1");
    std::cout << "\ta flag has been successfully created\n";
}

void game::object::Void::on_touch(const Player &player) {
    std::cout << "touched a player\n";
}