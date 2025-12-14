#include "scene.h"

#include <iostream>


game::Scene::Scene() {
    window = nullptr;
    fonts = nullptr;
    boombox = nullptr;
}
game::Scene::Scene(sf::RenderWindow *window_link, FontSource *fonts_link, BoomBox *boombox_link) {
    window = window_link;
    fonts = fonts_link;
    boombox = boombox_link;
}
int game::Scene::event(const sf::Event &event) { return 0; }
int game::Scene::proceed() { return 0; }
void game::Scene::on_start() {}
void game::Scene::on_end() {}

void game::Scene::set_callback(const std::string &value) { callback = value; }
std::string game::Scene::get_callback() { return callback; }
