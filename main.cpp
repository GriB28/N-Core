#include "game.h"
#include <iostream>
using std::cout;


int main() {
    cout << "R-0 is starting...\n";
    auto g = game::Engine(1280, 720);
    return 0;
}
