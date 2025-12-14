#include "platform.h"

#include <iostream>


game::object::Platform::Platform(
    const string &chapter_id, const short x, const short y,
    const bool is_spawn, const bool is_end, const bool has_ladder, const bool has_spikes
    ) : Object(chapter_id, x, y) {
    this->has_ladder = has_ladder;
    set_component("has_ladder", has_ladder);
    this->is_spawn = is_spawn;
    set_component("is_spawn", is_spawn);
    this->is_end = is_end;
    set_component("is_end", is_end);
    this->has_spikes = has_spikes;
    set_component("has_spikes", has_spikes);

    if (is_spawn)
        reset_sprite("flag_spawn");
    else if (is_end)
        reset_sprite("flag_end");
    else if (has_ladder)
        reset_sprite("platform_ladder");
    else if (has_spikes)
        reset_sprite("platform_spikes");
    else
        reset_sprite("platform");
    std::cout << "\ta platform has been successfully created\n";
}
void game::object::Platform::constant_position_delta() const {
    if (object_id == "platform_ladder")
        sprite->move(0, (1024-1260) * sprite->getScale().y);
}

bool game::object::Platform::is_blocked_move_origin(short x, short y) {
    return y == local_y + 1;
}
bool game::object::Platform::is_blocked_move_target(short x, short y) {
    return y == local_y + 1;
}

void game::object::Platform::walk_in(Player *player) {
    std::cout << "a player has walked in\n";
    if (has_spikes) player->die();
    else if (is_end) player->win();
}