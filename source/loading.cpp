#include "loading.h"
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "fonts.h"
using std::cout;


sf::RenderWindow *game::Loading::window;
sf::Music game::Loading::logo_sound = sf::Music("music/DSC0.flac");
sf::Text game::Loading::loading_text(Fonts::XKCD, "     R-0\n  loading", 120);


game::Loading::Loading(sf::RenderWindow *&window_link) {
    window = window_link;
    logo_sound.setLooping(false);
}
game::Loading::~Loading() = default;

void game::Loading::event(const std::optional<sf::Event> &event) {
    cout << "  > caught this event at 'Loading' class source\n    > ";
    if (event -> is<sf::Event::KeyPressed>()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
            cout << "<A> is pressed\n";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
            cout << "<space> is pressed\n";
    }
    cout << "\n\n";
}
void game::Loading::proceed() {
    cout << "  > now at 'Loading' class source\n    > ";
    window->draw(loading_text);
    cout << "\n\n";
}
