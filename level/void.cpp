#include "void.h"
#include "../player/player.h"

#include <iostream>


game::object::Void::Void(
    const string &chapter_id, const short x, const short y,
    const bool is_kill_zone
    ) : Object(chapter_id, x, y) {
    this->is_kill_zone = is_kill_zone;
    set_component("is_kill_zone", is_kill_zone);

    reset_sprite("void", "1");
    std::cout << "\ta flag has been successfully created\n";
}

void game::object::Void::walk_in(Player* player) {
    std::cout << "[void/walk_in]\tplayer instance: " << player << '\n';
    if (is_kill_zone) player->die();
}