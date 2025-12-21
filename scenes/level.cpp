#include "level.h"

#include <filesystem>
#include <iostream>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
using std::filesystem::exists;


game::Level::Level(sf::RenderWindow* window_link, FontSource* fonts_link, BoomBox* boombox_link) : Scene(window_link, fonts_link, boombox_link) {
    level_generator = nullptr;
    player = nullptr;

    bg = new sf::Sprite;
    day_texture = new sf::Texture;
    night_texture = new sf::Texture;

    raw_negative_shader = new sf::Shader;
    raw_negative_shader->loadFromFile("shaders/negative.frag", sf::Shader::Fragment);
    negative_shader = new sf::RenderStates;
    negative_shader->shader = raw_negative_shader;

    av = 0;
    av_counter = new sf::Text;
    av_counter->setFillColor(sf::Color(128, 128, 128));
    av_counter->setCharacterSize(50);
    av_counter->setFont(*fonts->pixel2());
    av_counter->setPosition(55, 5);
    av_counter_0 = new sf::Text;
    av_counter_0->setFillColor(sf::Color(128, 64, 64));
    av_counter_0->setCharacterSize(50);
    av_counter_0->setFont(*fonts->pixel2());
    av_counter_0->setPosition(55, 5);

    is_day = true;
    cycle_change_animation_flag = false;
    cycle_change_animation_phase = false;
}

void game::Level::clear_bg_textures() const {
    delete day_texture;
    delete night_texture;
}

game::Level::~Level() {
    delete level_generator;
    delete player;
    delete av_counter;
    delete bg;

    delete raw_negative_shader;
    delete negative_shader;

    clear_bg_textures();
}

int game::Level::event(const Event &event) {
    int return_code = 0;
    if (event.type == Event::KeyReleased)
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                return_code = 4;
                break;
            case sf::Keyboard::Space:
            case sf::Keyboard::Q:
                if (!cycle_change_animation_flag) {
                    cycle_change_animation_flag = true;
                    cycle_change_animation_phase = true;
                    is_day = !is_day;
                    cycle_change_clock.restart();
                }
                break;
            default:
                check_movement_keys(event.key.code);
                break;
        }

    return return_code;
}
void game::Level::check_movement_keys(const sf::Keyboard::Key &keycode) {
    const auto player_position = player->get_position();
    short x = player_position.x, y = player_position.y;
    std::cout << "[level/check_keys]\tplayer coords: " << x << ", " << y << '\n';

    bool do_move = true;
    short dx = 0, dy = 0;
    switch (keycode) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            dy = -1;
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            dx = -1;
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            dy = 1;
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            dx = 1;
            break;
        default:
            do_move = false;
            break;
    }
    if (do_move && !player->is_moving() && player->is_alive() &&
        0 <= x+dx && x+dx < level_generator->get_matrix_size().x &&
        0 <= y+dy && y+dy < level_generator->get_matrix_size().y) {
        auto origin = level_generator->get_tile(x, y);
        auto target = level_generator->get_tile(x+dx, y+dy);
        std::cout << "[level/move]\ttarget name: " << target->get_name() << '\n'
        << "\t\torigin: " << x << ':' << y << '\n'
        << "\t\ttarget: " << x+dx << ':' << y+dy << '\n';
        if (dx == 0 && (origin->get_object_id() == "ladder" || target->get_object_id() == "ladder")) {
            av_counter->setString(std::to_string(--av));
            while (((target->get_object_id() == "ladder" && dy < 0) ||
                    (!target->get_component("has_ladder") && dy > 0)) &&
                    !target->is_blocked_move_origin(x, y)) {
                origin->walk_out(player);
                player->move(0, dy);
                target->walk_in(player);

                origin = target;
                y += dy;
                target = level_generator->get_tile(x, y);
            }
        }
        else if (!target->is_blocked_move_origin(x, y) && !origin->is_blocked_move_target(x+dx, y+dy)) {
            av_counter->setString(std::to_string(--av));
            origin->walk_out(player);
            player->move(dx, dy);
            target->walk_in(player);

            x += dx;
            y += dy;
            while (target->get_object_id() == "void" && player->is_alive()) {
                origin = target;
                target = level_generator->get_tile(x, y + 1);
                if (!target->is_blocked_move_origin(x, y) && !origin->is_blocked_move_target(x, y + 1)) {
                    origin->walk_out(player);
                    player->move(0, 1);
                    target->walk_in(player);
                }
                y++;
            }
        }
        if (av == 0) {
            std::cout << "av = 0; player: " << x << ':' << y << ", end_pos: " << end_pos.x << ':' << end_pos.y << '\n';
            if (end_pos.x != x || end_pos.y != y) player->die();
            else player->win();
        }
    }
}

int game::Level::proceed() {
    window->draw(*bg);
    level_generator->render_level(window);
    player->draw_at(window);

    if (0 < av && av < 256) window->draw(*av_counter);
    else window->draw(*av_counter_0);

    if (cycle_change_animation_flag) {
        const auto t = cycle_change_clock.getElapsedTime().asMilliseconds();
        if (cycle_change_animation_phase) {
            if (t <= cycle_change_animation_time)
                bg->setColor(sf::Color(255, 255, 255, 255 * (1.f - t / cycle_change_animation_time)));
            else {
                cycle_change_clock.restart();
                cycle_change_animation_phase = false;
                bg->setTexture(is_day ? *day_texture : *night_texture);
                bg->setColor(sf::Color(255, 255, 255, 0));
            }
        }
        else {
            if (t <= cycle_change_animation_time)
                bg->setColor(sf::Color(255, 255, 255, 255 * (t / cycle_change_animation_time)));
            else {
                cycle_change_clock.restart();
                cycle_change_animation_flag = false;
                bg->setColor(sf::Color(255, 255, 255, 255));
            }
        }
    }

    return 0;
}

void game::Level::on_start(const std::string &level_info) {
    const float window_shrink = static_cast<float>(window->getSize().x) / 1920;
    clear_bg_textures();

    const auto sep = level_info.find('-');
    const auto chapter_id = level_info.substr(0, sep),
               level_id   = level_info.substr(sep + 1);
    bool have_shaded_tiles;

    level_generator = new object::Generator(chapter_id, level_id, av, have_shaded_tiles);
    av_counter->setString(std::to_string(av));
    std::cout << "[level] got av: " << av << ", av if-statement: av+1 = " << static_cast<unsigned short>(av + 1) << '\n';
    av_counter_0->setString(static_cast<unsigned short>(av + 1) == 0 ? "" : "0");
    level_generator->set_scale(global_scale * window_shrink);

    start_pos = level_generator->get_start_point();
    end_pos = level_generator->get_end_point();
    player = new Player("test", start_pos.x, start_pos.y);
    player->set_scale(global_scale * window_shrink);
    player->set_abs_offset(level_generator->auto_offset(window));

    day_texture = new sf::Texture;
    if (const std::string path = "level/bg/" + chapter_id + '/' + level_id + "-day.png"; exists(path))
        day_texture->loadFromFile(path);
    else day_texture->loadFromFile("level/bg/0.png");

    night_texture = new sf::Texture;
    if (const std::string path = "level/bg/" + chapter_id + '/' + level_id + "-night.png"; exists(path))
        night_texture->loadFromFile(path);
    else night_texture->loadFromFile("level/bg/0.png");

    bg->setTexture(*day_texture);
    bg->setScale(window_shrink, window_shrink);

    if (chapter_id == "ch0") current_ost = "DSC0";
    else if (chapter_id == "ch1") {
        if (level_id == "1" || level_id == "2") current_ost = "DSC8p1";
        else if (level_id == "3" || level_id == "4") current_ost = "DSC8p2";
        else current_ost = "DSC8f";
    }

    if (!current_ost.empty())
        boombox->get_track(current_ost)->play();
}
void game::Level::on_end() {
    if (!current_ost.empty())
        boombox->get_track(current_ost)->stop();
}
