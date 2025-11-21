#include "music.h"

Music *game::Music::DSC0_origin = new sf::Music();
Music *game::Music::DSC2_origin = new sf::Music();
Music *game::Music::DSC5_origin = new sf::Music();
Music *game::Music::loading_origin = new sf::Music();

game::Music::Music() {
    DSC0_origin->openFromFile("music/DSC0.ogg");
    DSC2_origin->openFromFile("music/DSC2.ogg");
    DSC5_origin->openFromFile("music/DSC5.ogg");
    loading_origin->openFromFile("music/horncall.ogg");

    DSC0_origin->setLoop(true);
    DSC5_origin->setLoop(true);
}
game::Music::~Music() {
    delete DSC0_origin;
    delete DSC2_origin;
    delete DSC5_origin;
    delete loading_origin;
}

game::Music* game::Music::instance() { return new Music(); }


Music* game::Music::DSC0() const { return DSC0_origin; }
Music* game::Music::DSC2() const { return DSC2_origin; }
Music* game::Music::DSC5() const { return DSC5_origin; }
Music* game::Music::loading() const { return loading_origin; }
