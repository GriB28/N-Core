#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


unsigned *n;

game::Game::Game() {
    n = new unsigned();
    main_theme = sf::Music("music/DSC0.flac");
    main_theme.play();
}

game::Game::~Game() {
    delete n;
}

void game::Game::loop(unsigned short X, unsigned short Y) {
    sf::RenderWindow window(sf::VideoMode({X, Y}), "d");
    const sf::Font font("fonts/XKCD.ttf");
    const sf::Text text(font, "     DSC0\n\n       D", 100);
    main_theme.setLooping(true);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event -> is<sf::Event::Closed>())
                window.close();
            else if (event -> is<sf::Event::KeyPressed>()) {
            }
        }
        window.clear();
        window.draw(text);
        window.display();
    }
}

void game::Game::loop() { loop(1280, 720); }
