#include "chapter_layout.h"
#include "../utils/numeric.h"

#include <iostream>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
using sf::Keyboard;
using std::cout;


game::ChapterLayout::ChapterLayout(sf::RenderWindow *window_link, FontSource *fonts_link, BoomBox *boombox_link) : Scene(window_link, fonts_link, boombox_link) {
    page = 0;

    page_swipe_animation_flag = false;
    delta_page = 0;
    target_page_animation_offset = 0;

    day_night_cycle_animation_flag = false;
    day_night_cycle = true;
    day_night_animation_phase = false;
}

void game::ChapterLayout::on_start() {
    const auto default_view = window->getDefaultView().getCenter();
    auto initial_view = window->getView();
    initial_view.setCenter(default_view.x + page * static_cast<float>(window->getSize().x), default_view.y);
    window->setView(initial_view);
    const unsigned window_x_size_origin = window->getSize().x,
                   window_y_size_origin = window->getSize().y;
    const auto window_x_size = static_cast<float>(window_x_size_origin),
               window_y_size = static_cast<float>(window_y_size_origin);
    const float window_x_shrink = window_x_size / 1920,
                window_y_shrink = window_y_size / 1080;

    cout << "[chapter_layout] initialised with window: x = " << window_x_size << ", y = " << window_y_size
    <<   ";\n                 shrink: x = " << window_x_shrink << ", y = " << window_y_shrink << "\n";

    for (short chapter_number = 0; chapter_number <= level_pages_cap; chapter_number++) {
        auto texture = new sf::Texture();
        if (0 < chapter_number && chapter_number < level_pages_cap)
            texture->loadFromFile("level/bg/chapter" + std::to_string(chapter_number) + "-day.png");
        else if (chapter_number == 0)
            texture->loadFromFile("level/bg/chapter0.png");
        else
            texture->loadFromFile("level/bg/0.png");
        splash_screens_day_textures.push_back(texture);

        auto s = new sf::Sprite();
        s->setTexture(*texture);
        s->setPosition(window_x_size * chapter_number, 0);
        s->setScale(window_x_shrink, window_y_shrink);
        splash_screens.push_back(s);

        texture = new sf::Texture();
        if (0 < chapter_number && chapter_number < level_pages_cap)
            texture->loadFromFile("level/bg/chapter" + std::to_string(chapter_number) + "-night.png");
        else
            texture->loadFromFile("level/bg/0.png");
        splash_screens_night_textures.push_back(texture);

        auto text = new sf::Text();
        switch (chapter_number) {
            case 0:
                text->setString("0. Tutorial");
                break;
            case 1:
                text->setString("1. Starfall Cliffs");
                break;
            default:
                text->setString("Coming soon...");
                break;
        }
        text->setCharacterSize(window_y_size_origin * 5 / 54);
        text->setFont(*fonts->PAG());
        text->setFillColor(sf::Color(255, 255, 255, 128));
        text->setPosition(
            (window_x_size - text->getGlobalBounds().width) / 2 + window_x_size * chapter_number,
            window_y_size / 12
            );
        if (chapter_number == level_pages_cap) text->move(0, window_y_size / 3);
        chapters_names.push_back(text);

        if (chapter_number < level_pages_cap) {
            levels.emplace_back(5);
            levels_buttons_textures.emplace_back(5);
            levels_buttons_texts.emplace_back(5);
            for (short btn = 1; btn <= 5; btn++) {
                levels[chapter_number][btn - 1] = new utils::Button;
                levels_buttons_textures[chapter_number][btn - 1] = std::pair(new sf::Texture, new sf::Texture);
                levels_buttons_textures[chapter_number][btn - 1].first->loadFromFile("resources/buttons/chapter_layout/1-4.png");
                levels_buttons_textures[chapter_number][btn - 1].second->loadFromFile("resources/buttons/chapter_layout/1-4 dim.png");
                levels_buttons_texts[chapter_number][btn - 1] = new sf::Text;
                levels_buttons_texts[chapter_number][btn - 1]->setCharacterSize(50);
                levels_buttons_texts[chapter_number][btn - 1]->setFont(*fonts->pixel2());
                levels_buttons_texts[chapter_number][btn - 1]->setFillColor(sf::Color(2, 2, 2));
                levels_buttons_texts[chapter_number][btn - 1]->setString(std::to_string(btn));
                levels[chapter_number][btn - 1]->initialize(
                    levels_buttons_texts[chapter_number][btn - 1],
                    levels_buttons_textures[chapter_number][btn - 1].first,
                    levels_buttons_textures[chapter_number][btn - 1].second
                    );
                levels[chapter_number][btn - 1]->set_scale(.5);
                switch (btn) {
                    case 1:
                        levels[chapter_number][0]->set_position(
                            280 * window_x_shrink + window_x_size * chapter_number,
                            500 * window_y_shrink
                            );
                        break;
                    case 2:
                        levels[chapter_number][1]->set_position(
                            530 * window_x_shrink + window_x_size * chapter_number,
                            760 * window_y_shrink
                            );
                        break;
                    case 3:
                        levels[chapter_number][2]->set_position(
                            880 * window_x_shrink + window_x_size * chapter_number,
                            500 * window_y_shrink
                            );
                        break;
                    case 4:
                        levels[chapter_number][3]->set_position(
                            1230 * window_x_shrink + window_x_size * chapter_number,
                            760 * window_y_shrink
                            );
                        break;
                    case 5:
                        levels[chapter_number][4]->set_position(
                            1480 * window_x_shrink + window_x_size * chapter_number,
                            500 * window_y_shrink
                            );
                        break;
                    default:
                        break;
                }
                levels_buttons_texts[chapter_number][btn - 1]->move(-10, 10);
            }
        }
    }

    day_night_clock.restart();
    boombox->get_track("DSC2")->play();
}
void game::ChapterLayout::on_end() {
    window->setView(window->getDefaultView());

    for (const auto s : splash_screens) delete s;
    for (const auto t : splash_screens_day_textures) delete t;
    for (const auto t : splash_screens_night_textures) delete t;
    for (const auto t : chapters_names) delete t;
    splash_screens.clear();
    splash_screens_day_textures.clear();
    splash_screens_night_textures.clear();
    chapters_names.clear();

    for (short p = 0; p < level_pages_cap; p++) {
        for (const auto b : levels[p]) delete b;
        for (const auto tt : levels_buttons_textures[p]) {
            delete tt.first;
            delete tt.second;
        }
        for (const auto t : levels_buttons_texts[p]) delete t;
        levels[p].clear();
        levels_buttons_textures[p].clear();
        levels_buttons_texts[p].clear();
    }
    levels.clear();
    levels_buttons_textures.clear();
    levels_buttons_texts.clear();

    boombox->get_track("DSC2")->stop();
}

game::ChapterLayout::~ChapterLayout() {
    on_end();
}

void game::ChapterLayout::start_page_animation_sequence() {
    swipe_clock.restart();
    page_swipe_animation_flag = true;
    current_view = window->getView();
    initial_view_center = current_view.getCenter();
    target_page_animation_offset = delta_page * static_cast<float>(window->getSize().x);
    cout << "\nstarted sequence\ncurrent x: " << current_view.getCenter().x << " (= initial), target delta x: " << target_page_animation_offset << '\n';
}

int game::ChapterLayout::event(const Event &event) {
    int return_code = 0;
    if (event.type == Event::KeyReleased) {
        if (event.key.code == Keyboard::Escape) return_code = 2;
        else if (!page_swipe_animation_flag) {
            switch (event.key.code) {
                case Keyboard::Right:
                    delta_page = 1;
                    if (++page > level_pages_cap) {
                        page = 0;
                        delta_page = -level_pages_cap;
                    }
                    start_page_animation_sequence();
                    break;
                case Keyboard::D:
                    delta_page = 1;
                    if (++page > level_pages_cap) {
                        page = 0;
                        delta_page = -level_pages_cap;
                    }
                    start_page_animation_sequence();
                    break;
                case Keyboard::Left:
                    delta_page = -1;
                    if (--page < 0) {
                        page = level_pages_cap;
                        delta_page = level_pages_cap;
                    }
                    start_page_animation_sequence();
                    break;
                case Keyboard::A:
                    delta_page = -1;
                    if (--page < 0) {
                        page = level_pages_cap;
                        delta_page = level_pages_cap;
                    }
                    start_page_animation_sequence();
                    break;
                default:
                    break;
            }
        }
    }
    else if (event.type == Event::MouseButtonPressed && page < level_pages_cap) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            const auto mouse_abs_position = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            for (const auto btn : levels[page])
                btn->check_click(mouse_abs_position.x, mouse_abs_position.y);
        }
    }
    else if (event.type == Event::MouseButtonReleased && page < level_pages_cap) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            const auto mouse_abs_position = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            for (const auto btn : levels[page])
                btn->check_release(mouse_abs_position.x, mouse_abs_position.y);
        }
    }

    if (page < level_pages_cap)
        for (short i = 0; i < 5; i++)
            if (levels[page][i]->is_clicked()) {
                set_callback("ch" + std::to_string(page) + '-' + std::to_string(i + 1));
                return_code = 3;
                break;
            }

    return return_code;
}

int game::ChapterLayout::proceed() {
    int return_code = 0;

    for (short i = page <= 1 ? 0 : page - 1; i <= (page + 1 >= level_pages_cap ? level_pages_cap : page + 1); i++) {
        window->draw(*splash_screens[i]);
        window->draw(*chapters_names[i]);
        if (i < level_pages_cap) for (const auto btn : levels[i]) btn->draw_at(window);
    }

    if (day_night_clock.getElapsedTime().asMilliseconds() >= day_night_animation_delay) {
        day_night_clock.restart();
        day_night_cycle_animation_flag = true;
        day_night_cycle = !day_night_cycle;
        day_night_animation_phase = true;
    }

    if (day_night_cycle_animation_flag) {
        const auto t = day_night_clock.getElapsedTime().asMilliseconds();
        if (day_night_animation_phase) {
            if (t <= day_night_animation_time)
                for (const auto bg : splash_screens)
                    bg->setColor(sf::Color(255, 255, 255, 255 * (1.f - t / day_night_animation_time)));
            else {
                day_night_clock.restart();
                day_night_animation_phase = false;
                for (unsigned short i = 0; i < splash_screens.size(); i++) {
                    splash_screens[i]->setTexture(day_night_cycle ? *splash_screens_day_textures[i] : *splash_screens_night_textures[i]);
                    splash_screens[i]->setColor(sf::Color(255, 255, 255, 0));
                }
            }
        }
        else {
            if (t <= day_night_animation_time)
                for (const auto bg : splash_screens)
                    bg->setColor(sf::Color(255, 255, 255, 255 * (t / day_night_animation_time)));
            else {
                day_night_clock.restart();
                day_night_cycle_animation_flag = false;
                for (const auto bg : splash_screens)
                    bg->setColor(sf::Color(255, 255, 255, 255));
            }
        }
    }

    if (page_swipe_animation_flag) {
        if (const auto t = swipe_clock.getElapsedTime().asMilliseconds(); t <= day_night_animation_time) {
            current_view.setCenter(
                initial_view_center.x + target_page_animation_offset * numeric::sine(t, day_night_animation_time),
                initial_view_center.y
                );
            window->setView(current_view);
        }
        else {
            page_swipe_animation_flag = false;
            current_view.setCenter(initial_view_center.x + target_page_animation_offset, initial_view_center.y);
            window->setView(current_view);
        }
    }

    return return_code;
}
