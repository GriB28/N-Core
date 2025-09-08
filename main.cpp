#include "game.h"
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")


int main() {
    auto g = game::Game();
    g.loop();
    return 0;
}
// https://github.com/GriB28/game-beta.git
