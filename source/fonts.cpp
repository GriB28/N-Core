#include "fonts.h"

sf::Font* game::Fonts::XKCD_origin = new sf::Font();
sf::Font* game::Fonts::PAG_origin = new sf::Font();
sf::Font* game::Fonts::OCRA_origin = new sf::Font();
sf::Font* game::Fonts::Penacony_origin = new sf::Font();

game::Fonts::Fonts() {
    XKCD_origin->loadFromFile("fonts/XKCD.ttf");
    PAG_origin->loadFromFile("fonts/PAG Norm.ttf");
    OCRA_origin->loadFromFile("fonts/OCR A Extended Regular.ttf");
    Penacony_origin->loadFromFile("fonts/HSR Penacony Regular.ttf");
}
game::Fonts::~Fonts() {
    delete XKCD_origin;
    delete PAG_origin;
    delete OCRA_origin;
    delete Penacony_origin;
}

game::Fonts* game::Fonts::instance() { return new Fonts(); }


sf::Font* game::Fonts::XKCD() const     { return XKCD_origin; }
sf::Font* game::Fonts::PAG() const      { return PAG_origin; }
sf::Font* game::Fonts::OCRA() const     { return OCRA_origin; }
sf::Font* game::Fonts::Penacony() const { return Penacony_origin; }
