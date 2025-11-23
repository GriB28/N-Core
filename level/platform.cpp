#include "platform.h"

#include <iostream>


game::object::Platform::Platform(const std::string &chapter_id, const bool &is_spawn, const bool &is_end, const bool &has_ladder) : Object(chapter_id) {
    this->has_ladder = has_ladder;
    this->is_spawn = is_spawn;
    this->is_end = is_end;

    if (is_spawn)
        reset_sprite("flag_spawn");
    else if (is_end)
        reset_sprite("flag_end");
    else if (has_ladder)
        reset_sprite("platform_ladder");
    else
        reset_sprite("platform");
    std::cout << "\ta platform has been successfully created\n";
}
void game::object::Platform::constant_position_delta() {
    if (object_id == "platform_ladder")
        sprite->move(0, (1024-1260) * sprite->getScale().y);
}

void game::object::Platform::on_touch(const Player &player) {
    std::cout << "touched a player\n";
}