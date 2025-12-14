#include "game.h"
#include "scenes/level.h"
#include "scenes/loading.h"
#include "scenes/main_menu.h"
#include "scenes/chapter_layout.h"

#include <SFML/Window/Event.hpp>
using std::to_string;


game::Engine::Engine(const unsigned short x, const unsigned short y, FontSource *fonts_link) {
    if (fonts_link == nullptr) fonts_link = FontSource::instance();

    current_scene_index = 0;

    window = new sf::RenderWindow(sf::VideoMode({x, y}), "Cores loading...");
    // window->setFramerateLimit(120);
    closing_flag = false;
    fonts = fonts_link;

    chapter_layout_theme = new Soundtrack("music/DSC2.ogg");
    chapter_layout_theme->set_loop(true);
    menu_theme = new Soundtrack("music/DSC6.ogg");
    menu_theme->set_loop(true);
    chapter0   = new Soundtrack("music/DSC0.ogg");
    chapter1_1 = new Soundtrack("music/DSC8p1.ogg");
    chapter1_1->set_loop(true);
    chapter1_2 = new Soundtrack("music/DSC8p2.ogg");
    chapter1_2->set_loop(true);
    chapter1_f = new Soundtrack("music/DSC8f.ogg");
    chapter1_f->set_loop(true);

    loading_boombox = new BoomBox;
    loading_boombox->add_track(chapter_layout_theme);
    loading_boombox->add_track(menu_theme);
    level_boombox = new BoomBox;
    level_boombox->add_track(chapter0);
    level_boombox->add_track(chapter1_1);
    level_boombox->add_track(chapter1_2);
    level_boombox->add_track(chapter1_f);

    level_link = new Level(window, fonts, level_boombox);
    scenes = new Scene*[scenes_cap+1];
    scenes[0] = new Scene; // void scene
    scenes[1] = new Loading(window, fonts, loading_boombox);
    scenes[2] = new MainMenu(window, fonts, loading_boombox);
    scenes[3] = level_link;
    scenes[4] = new ChapterLayout(window, fonts, loading_boombox);

    fps.setCharacterSize(10);
    fps.setFont(*fonts->OCRA());
    fps_delta.setCharacterSize(10);
    fps_delta.setFont(*fonts->OCRA());
    frames = 0;
    last_fps_update_value = 0;
    fps_timer.restart();

    mouse_position.setCharacterSize(10);
    mouse_position.setFont(*fonts->OCRA());
    mouse_position.setFillColor(sf::Color(147, 147, 147, 141));

    scene_num.setCharacterSize(10);
    scene_num.setFont(*fonts->OCRA());
    scene_num.setFillColor(sf::Color(147, 147, 147, 141));

    version_info.setCharacterSize(12);
    version_info.setFont(*fonts->OCRA());
    version_info.setFillColor(sf::Color(147, 147, 147, 141));
    version_info.setString("beta-1b25-indev");

    update_scene_index(1);
    loop();
}
game::Engine::~Engine() {
    for (unsigned short i = 0; i <= scenes_cap; i++) delete scenes[i];
    delete[] scenes;

    delete menu_theme;
    delete chapter_layout_theme;
    delete chapter0;
    delete chapter1_1;
    delete chapter1_2;
    delete chapter1_f;

    delete fonts;
    delete loading_boombox;
    delete level_boombox;

    delete window;
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

        if (fps_timer.getElapsedTime().asMilliseconds() >= 500) {
            frames = static_cast<unsigned short>(static_cast<float>(frames) / fps_timer.getElapsedTime().asSeconds());
            const auto window_x_max_coord = window->getView().getCenter().x + static_cast<float>(window->getSize().x) / 2;
            const auto window_y_max_coord = window->getView().getCenter().y + static_cast<float>(window->getSize().y) / 2;

            if (last_fps_update_value < frames)
                fps_delta.setFillColor(sf::Color(0, 147, 20, 141));
            else if (last_fps_update_value > frames)
                fps_delta.setFillColor(sf::Color(255, 29, 0, 141));
            else
                fps_delta.setFillColor(sf::Color(147, 147, 147, 141));
            fps_delta.setString((frames - last_fps_update_value > 0 ? "(+" : "(") + to_string(frames - last_fps_update_value) + ')');
            fps_delta.setPosition(window_x_max_coord - 40, 15);

            fps.setString(to_string(frames));
            fps.setPosition(window_x_max_coord - 35, 5);

            last_fps_update_value = frames;
            frames = 0;
            fps_timer.restart();

            const auto local_mouse_position = sf::Mouse::getPosition(*window);
            mouse_position.setString(
                to_string(local_mouse_position.x)
                + "\n ~\n"
                + std::to_string(local_mouse_position.y)
                );
            mouse_position.setPosition(window_x_max_coord - 35, 30);

            scene_num.setPosition(window_x_max_coord - 50, 65);

            version_info.setPosition(window_x_max_coord - window->getSize().x + 5, window_y_max_coord - 15);
        }

        window->draw(fps);
        window->draw(fps_delta);
        window->draw(mouse_position);
        window->draw(scene_num);
        window->draw(version_info);
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
        std::string local_callback;
        if (current_scene_index > 0) {
            scenes[current_scene_index]->on_end();
            local_callback = scenes[current_scene_index]->get_callback();
        }
        current_scene_index = return_code;
        scene_num.setString("scene " + to_string(current_scene_index));
        if (current_scene_index < 0) closing_flag = true;
        else {
            if (current_scene_index == 3) level_link->on_start(local_callback);
            else scenes[current_scene_index]->on_start();
        }
    }
}
