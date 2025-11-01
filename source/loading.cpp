#include "loading.h"

#include <iostream>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
using std::cout;
using std::string;
using sf::Event;
using sf::Keyboard;


game::Loading::Loading(sf::RenderWindow *&window_link, Fonts *&fonts_link) {
    window = window_link;
    fonts = fonts_link;

    logo_sound.openFromFile("music/DSC2.flac");
    logo_sound.setLoop(false);

    loading_text.setFont(*fonts->XKCD());
    loading_text.setString("EXOMYTH-8...");
    loading_text.setCharacterSize(60);
    loading_text.setPosition(470, 300);

    awaiting_text.setFont(*fonts->PAG());
    awaiting_text.setString("press Space to continue");
    awaiting_text.setCharacterSize(20);
    awaiting_text.setPosition(400, 600);
    awaiting_flag = false;

    frogl2_counter = 10;
    frogl2_fading_flag = false;
    frogl2_alpha_fading = 0;
    frogl2.setPosition(1280 * (1 - .2) / 2, 400);
    frogl2.setScale(.2, .2);
}
game::Loading::~Loading() {
    delete fonts;
}

int game::Loading::event(const Event &event) {
    int return_code;
    if (event.type == Event::KeyPressed) {
        switch (event.key.code) {
            case Keyboard::A:
                cout << "<A> is pressed\n";
                return_code = 0;
                break;
            case Keyboard::Space:
                cout << "<space> is pressed\n";
                return_code = 1;
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
    return return_code;
}
int game::Loading::proceed() {
    int return_code = 0;

    if (frogl2_counter < 39 * 7 + 1) {
        frogl2_texture.loadFromFile("resources/frogl2/" + std::to_string(frogl2_counter / 7) + ".jpg");
        frogl2.setTexture(frogl2_texture);
        frogl2_counter++;
    }
    if (frogl2_counter == 39 * 3) frogl2_fading_flag = true;

    if (frogl2_fading_flag) {
        if (frogl2_alpha_fading > 5 && frogl2.getColor().a > 0) {
            frogl2_alpha_fading = -1;
            frogl2.setColor(sf::Color(255, 255, 255, frogl2.getColor().a - 1));
        }
        frogl2_alpha_fading++;
    }

    if (frogl2.getColor().a == 0) awaiting_flag = true;

    if (awaiting_flag) {

    }

    window->draw(frogl2);
    window->draw(loading_text);
    return return_code;
}

void game::Loading::on_start() {
    logo_sound.play();
}
void game::Loading::on_end() {
    logo_sound.stop();
    sf::View worldview(window->getDefaultView());
    worldview.setCenter(960, 540);
    window->setSize(sf::Vector2u(1920, 1080));
}
