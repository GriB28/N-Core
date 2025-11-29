#include "game.h"
#include "scenes/level.h"
#include "scenes/loading.h"
#include "scenes/main_menu.h"

#include <SFML/Window/Event.hpp>
#include <chrono>
using std::to_string;


game::Engine::Engine(const unsigned short x, const unsigned short y, Fonts *fonts_link, Music *music_link) {
    if (fonts_link == nullptr) fonts_link = Fonts::instance();
    if (music_link == nullptr) music_link = Music::instance();
    initialize(x, y, fonts_link, music_link);
}
void game::Engine::initialize(const unsigned short x, const unsigned short y, Fonts *fonts_link, Music *music_link) {
    current_scene_index = 0;

    window = new sf::RenderWindow(sf::VideoMode({x, y}), "DSC");
    // window->setFramerateLimit(120);
    closing_flag = false;
    fonts = fonts_link;
    music = music_link;
    scenes = new Scene*[3+1];
    scenes[0] = new Scene; // void scene
    scenes[1] = new Loading(window, fonts, music);
    scenes[2] = new MainMenu(window, fonts, music);
    scenes[3] = new Level(window, fonts, music);

    fps.setCharacterSize(10);
    fps.setFont(*fonts->OCRA());
    fps_delta.setCharacterSize(10);
    fps_delta.setFont(*fonts->OCRA());
    frames = 0;
    last_fps_update = 0;
    last_fps_update_value = 0;

    mouse_position.setCharacterSize(10);
    mouse_position.setFont(*fonts->OCRA());
    mouse_position.setFillColor(sf::Color(147, 147, 147, 141));

    scene_num.setCharacterSize(10);
    scene_num.setFont(*fonts->OCRA());
    scene_num.setFillColor(sf::Color(147, 147, 147, 141));

    update_scene_index(1);
    loop();
}
game::Engine::~Engine() {
    delete window;

    for (unsigned short i = 0; i < 4; i++) delete scenes[i];
    delete[] scenes;

    delete fonts;
    delete music;
}


void game::Engine::loop() {
    Event event{};

    while (window->isOpen()) {
        window->clear();

        while (window->pollEvent(event)) {
            proceed_event_on_scenes(event);
            if (event.type == Event::Closed) {
                window->close();
                return;
            }
        }
        proceed_scenes();

        if (const auto t = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
            ).count(); t - last_fps_update >= 500000) {
            frames = static_cast<unsigned short>(frames / (static_cast<double>(t - last_fps_update) / 1000000));
            const auto window_x_size = static_cast<float>(window->getSize().x);

            if (last_fps_update_value < frames)
                fps_delta.setFillColor(sf::Color(0, 147, 20, 141));
            else if (last_fps_update_value > frames)
                fps_delta.setFillColor(sf::Color(255, 29, 0, 141));
            else
                fps_delta.setFillColor(sf::Color(147, 147, 147, 141));
            fps_delta.setString((frames - last_fps_update_value > 0 ? "(+" : "(") + to_string(frames - last_fps_update_value) + ')');
            fps_delta.setPosition(window_x_size - 40, 15);

            fps.setString(to_string(frames));
            fps.setPosition(window_x_size - 35, 5);

            last_fps_update = t;
            last_fps_update_value = frames;
            frames = 0;

            const auto local_mouse_position = sf::Mouse::getPosition(*window);
            mouse_position.setString(
                to_string(local_mouse_position.x)
                + "\n ~\n"
                + std::to_string(local_mouse_position.y)
                );
            mouse_position.setPosition(window_x_size - 35, 30);

            scene_num.setPosition(window_x_size - 50, 65);
        }

        window->draw(fps);
        window->draw(fps_delta);
        window->draw(mouse_position);
        window->draw(scene_num);
        window->display();
        frames++;

        if (closing_flag) window->close();
    }
}

void game::Engine::proceed_event_on_scenes(const Event &event) {
    if (current_scene_index > 0) {
        const int return_code = scenes[current_scene_index]->event(event);
        update_scene_index(return_code);
    }
}
void game::Engine::proceed_scenes() {
    if (current_scene_index > 0) {
        const int return_code = scenes[current_scene_index]->proceed();
        update_scene_index(return_code);
    }
}

void game::Engine::update_scene_index(const int return_code) {
    if (return_code != 0) {
        if (current_scene_index > 0)
            scenes[current_scene_index]->on_end();
        current_scene_index = return_code;
        scene_num.setString("scene " + to_string(current_scene_index));
        if (current_scene_index < 0) closing_flag = true;
        else scenes[current_scene_index]->on_start();
    }
}
