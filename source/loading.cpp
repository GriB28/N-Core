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
game::Loading::~Loading() {
    delete fonts;
}

int game::Loading::event(const sf::Event &event) {
    int return_code;
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::A:
                cout << "<A> is pressed\n";
                return_code = 0;
                break;
            case sf::Keyboard::Space:
                cout << "<space> is pressed\n";
                return_code = 0;
                break;
            default:
                cout << "another key is pressed\n";
                return_code = 0;
                break;
        }
    }
    else {
        return_code = 0;
    }
    cout << "\n\n";
    return return_code;
}
int game::Loading::proceed() {
    int return_code = 0;
    window->draw(loading_text);
    return return_code;
}
int game::Loading::on_start() {
    int return_code = 0;
    logo_sound.play();
    return return_code;
}
