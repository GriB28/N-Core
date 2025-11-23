#include "scene.h"

#include <iostream>


game::Scene::Scene() {
    window = nullptr;
    fonts = nullptr;
    music = nullptr;
}
game::Scene::Scene(sf::RenderWindow *window_link, Fonts *fonts_link, Music *music_link) {
    window = window_link;
    fonts = fonts_link;
    music = music_link;
}
int game::Scene::event(const sf::Event &event) { return 0; }
int game::Scene::proceed() { return 0; }
void game::Scene::on_start() {}
void game::Scene::on_end() {}
