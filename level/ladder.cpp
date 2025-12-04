#include "ladder.h"

#include <iostream>


game::object::Ladder::Ladder(
    const string &chapter_id, const short x, const short y
    ) : Object(chapter_id, x, y) {
    reset_sprite("ladder", "1");
    std::cout << "\ta ladder has been successfully created\n";
}
void game::object::Ladder::constant_position_delta() const {
    sprite->move(0, (1024-1260) * y_scale);
}
