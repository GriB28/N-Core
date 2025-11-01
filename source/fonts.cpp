#include "fonts.h"
#include <SFML/Graphics/Font.hpp>

sf::Font *game::Fonts::XKCD_origin = new sf::Font();
sf::Font *game::Fonts::PAG_origin = new sf::Font();

game::Fonts::Fonts() {
    XKCD_origin->loadFromFile("fonts/XKCD.ttf");
    PAG_origin->loadFromFile("fonts/PAG Norm.ttf");
}
game::Fonts::~Fonts() {
    delete XKCD_origin;
    delete PAG_origin;
}

game::Fonts* game::Fonts::instance() { return new Fonts(); }


sf::Font *game::Fonts::XKCD() { return XKCD_origin; }
sf::Font *game::Fonts::PAG() { return PAG_origin; }
