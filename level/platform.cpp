#include "platform.h"

#include <iostream>


game::object::Platform::Platform(const bool &has_flag, const bool &is_spawn, const bool &has_ladder) {
    this->has_ladder = has_ladder;
    this->has_flag = has_flag;
    this->is_spawn = is_spawn;
    if (!has_flag)
        reset_sprite("platform");
    else if (is_spawn)
        reset_sprite("platform_spawn");
    else
        reset_sprite("platform_end");
    std::cout << "\ta platform has been successfully created\n";
}

void game::object::Platform::on_touch(const Player &player) {
    std::cout << "touched a player\n";
}