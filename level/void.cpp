#include "void.h"

#include <iostream>


game::object::Void::Void() {
    reset_sprite("void");
    std::cout << "\ta flag has been successfully created\n";
}

void game::object::Void::on_touch(const Player &player) {
    std::cout << "touched a player\n";
}