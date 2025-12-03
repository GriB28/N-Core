#include "ladder.h"

#include <iostream>


game::object::Ladder::Ladder(const string &chapter_id) : Object(chapter_id) {
    reset_sprite("ladder", "1");
    std::cout << "\ta ladder has been successfully created\n";
}
void game::object::Ladder::constant_position_delta() {
    sprite->move(0, (1024-1260) * sprite->getScale().y);
}

void game::object::Ladder::interact(Player *player) {
    std::cout << "touched a player\n";
}