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
    loading_text.setString("|GriB28| presents...");
    loading_text.setCharacterSize(60);
    loading_text.setPosition((window->getSize().x - loading_text.getGlobalBounds().width) / 2, 300);

    awaiting_text = new sf::Text;
    awaiting_text->setFont(*fonts->PAG());
    awaiting_text->setString("press Space to continue");
    awaiting_text->setCharacterSize(20);
    awaiting_text->setFillColor(sf::Color(255, 255, 255, 0));
    awaiting_text_void_texture = new sf::Texture();
    awaiting_text_void_texture->loadFromFile("sprites/void.png");
    awaiting_button.init(&awaiting_text, &awaiting_text_void_texture, &awaiting_text_void_texture);
    awaiting_button.set_default_sprite_scale(250, 30);
    awaiting_button.set_clicked_sprite_scale(250, 30);
    awaiting_button.set_position((window->getSize().x - awaiting_text->getGlobalBounds().width) / 2, 600);
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
    if (event.type == Event::KeyPressed)
        switch (event.key.code) {
            case Keyboard::Escape:
                return_code = -2056;
                break;
            case Keyboard::Space:
                return_code = awaiting_flag;
                break;
            default:
                return_code = 0;
                break;
        }
    else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
        awaiting_button.check_click(event.mouseButton.x, event.mouseButton.y);
        if (awaiting_button.is_clicked()) return_code = awaiting_flag;
        else return_code = 0;
    }
    else return_code = 0;

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
    if (frogl2_counter == 96 * 7 / 8) frogl2_fading_flag = true;

    if (frogl2_fading_flag && frogl2.getColor().a > 1) {
        loading_text.setFillColor(sf::Color(255, 255, 255, frogl2.getColor().a - 1));
        frogl2.setColor(sf::Color(255, 255, 255, frogl2.getColor().a - 1));
    }
    else if (frogl2.getColor().a == 1) frogl2.setColor(sf::Color(255, 255, 255, 0));
    if (frogl2.getColor().a == 0) awaiting_flag = true;

    if (awaiting_flag && awaiting_text->getFillColor().a < 255)
        awaiting_text->setFillColor(sf::Color(255, 255, 255, awaiting_text->getFillColor().a + 1));


    window->draw(frogl2);
    window->draw(loading_text);
    awaiting_button.draw_at(window);
    return 0;
}

void game::Loading::on_start() {
    logo_sound.play();
}
void game::Loading::on_end() {
    logo_sound.stop();
    window->close();
    delete window;
    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "N-Core", sf::Style::Fullscreen);
    auto icon = sf::Image();
    icon.loadFromFile("icons/test.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
