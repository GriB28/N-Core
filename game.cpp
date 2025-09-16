#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using std::cout;


unsigned *n;

game::Game::Game() {
    n = new unsigned[4];
    virtualKeyboard = false;
    main_theme = sf::Music("music/DSC0.flac");
    main_theme.play();
}

game::Game::~Game() {
    delete n;
}

void game::Game::loop(unsigned short X, unsigned short Y) {
    sf::RenderWindow window(sf::VideoMode({X, Y}), "d");
    const sf::Font font("fonts/XKCD.ttf");
    const sf::Text text(font, "     DSC0", 100);
    main_theme.setLooping(true);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event -> is<sf::Event::Closed>())
                window.close();
            else if (event -> is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
                    std::cout << "'A' is pressed\n";
                    if (virtualKeyboard)
                        sf::Keyboard::setVirtualKeyboardVisible(true);
                    else
                        sf::Keyboard::setVirtualKeyboardVisible(false);
                }
            }
        }
        window.clear();
        window.draw(text);
        window.display();
    }
}

void game::Game::loop() { loop(1280, 720); }
