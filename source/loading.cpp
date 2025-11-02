#include "loading.h"

#include <iostream>
#include <chrono>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
using std::cout;
using std::string;
using sf::Event;
using sf::Keyboard;


long long get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::system_clock::now().time_since_epoch()).count();
}

game::Loading::Loading(sf::RenderWindow *&window_link, Fonts *&fonts_link) {
    window = window_link;
    fonts = fonts_link;

    logo_sound.openFromFile("music/DSC2.flac");
    logo_sound.setLoop(false);

    loading_text.setFont(*fonts->XKCD());
    loading_text.setString("project DSC");
    loading_text.setCharacterSize(60);
    loading_text.setPosition((window->getSize().x - loading_text.getGlobalBounds().width) / 2, 300);

    awaiting_text.setFont(*fonts->PAG());
    awaiting_text.setString("press Space to continue");
    awaiting_text.setCharacterSize(20);
    awaiting_text.setPosition((window->getSize().x - awaiting_text.getGlobalBounds().width) / 2, 600);
    awaiting_text.setFillColor(sf::Color(255, 255, 255, 0));
    awaiting_flag = false;

    frogl2_counter = 0;
    frogl2_fading_flag = false;
    frogl2_alpha_fading = 0;
    frogl2_timer = get_time();
    frogl2_frame_timestamp = 1000000 / 25;
    frogl2.setPosition(1280 * .8 / 2, 400);
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
                return_code = awaiting_flag;
                break;
            default:
                cout << "another key is pressed\n";
                return_code = 0;
                break;
        }
    }
    else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
        if (awaiting_text.getGlobalBounds().left - 10 <= event.touch.x &&
            event.touch.x <= awaiting_text.getGlobalBounds().left + awaiting_text.getGlobalBounds().width + 10 &&
            awaiting_text.getGlobalBounds().top + 10 >= event.touch.y &&
            event.touch.y >= awaiting_text.getGlobalBounds().top - awaiting_text.getGlobalBounds().height - 10)
            return_code = awaiting_flag;
        else return_code = 0;
    }
    else {
        return_code = 0;
    }
    return return_code;
}
int game::Loading::proceed() {
    if (frogl2_counter < 96) {
        if (get_time() - frogl2_timer >= frogl2_frame_timestamp) {
            frogl2_texture.loadFromFile("resources/frogl2/" + std::to_string(frogl2_counter) + ".jpg");
            frogl2.setTexture(frogl2_texture);
            frogl2_counter++;
            frogl2_timer = get_time();
        }
    }
    if (frogl2_counter == 96 / 8 * 7) frogl2_fading_flag = true;

    if (frogl2_fading_flag && frogl2.getColor().a > 1)
        frogl2.setColor(sf::Color(255, 255, 255, frogl2.getColor().a - 1));
    else if (frogl2.getColor().a == 1) frogl2.setColor(sf::Color(255, 255, 255, 0));
    if (frogl2.getColor().a == 0) awaiting_flag = true;

    if (awaiting_flag && awaiting_text.getFillColor().a < 255)
        awaiting_text.setFillColor(sf::Color(255, 255, 255, awaiting_text.getFillColor().a + 1));


    window->draw(frogl2);
    window->draw(loading_text);
    window->draw(awaiting_text);
    return 0;
}

void game::Loading::on_start() {
    logo_sound.play();
}
void game::Loading::on_end() {
    logo_sound.stop();
    window->close();
    delete window;
    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Exomyth", sf::Style::Fullscreen);
    auto icon = sf::Image();
    icon.loadFromFile("icons/test.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
