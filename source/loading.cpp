#include "loading.h"
#include "fonts.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
using std::cout;


sf::RenderWindow *game::Loading::window;
game::Fonts *game::Loading::fonts;
sf::Music game::Loading::logo_sound = sf::Music();
sf::Text game::Loading::loading_text = sf::Text();


game::Loading::Loading(sf::RenderWindow *&window_link, Fonts *&fonts_link) {
    window = window_link;
    fonts = fonts_link;

    loading_text.setFont(*fonts->XKCD());
    loading_text.setString("loading...");
    loading_text.setCharacterSize(120);

    logo_sound.openFromFile("music/DSC0.flac");
    logo_sound.setLoop(false);
}
game::Loading::~Loading() = default;

void game::Loading::event(const sf::Event &event) {
    cout << "  > caught this event at 'Loading' class source\n    > ";
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::A:
                cout << "<A> is pressed\n";
            case sf::Keyboard::Space:
                cout << "<space> is pressed\n";
            default:
                cout << "another key is pressed\n";
        }
    }
    cout << "\n\n";
}
void game::Loading::proceed() {
    cout << "  > now at 'Loading' class source\n    > ";
    window->draw(loading_text);
    cout << "\n\n";
}
