#include "platform.h"

#include <iostream>


game::object::Platform::Platform(const bool &has_ladder) {
    reset_sprite("platform");
    this->has_ladder = has_ladder;
    std::cout << "\ta platform has been successfully created\n";
}

void game::object::Platform::on_touch(const Player &player) {
    std::cout << "touched a player\n";
}