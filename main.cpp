/*
    Copyright 2023 Patricia Antlitz
*/
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Universe.hpp"
#include "CelestialBody.hpp"

int main(int argc, char const *argv[]) {
    // command-line arguments, T and delta t
    if (argc != 3) {
        std::cerr << "Args: " << argv[0] << " <T> <Delta t>" << std::endl;
        return 1;
    }

    double T = std::stod(argv[1]);
    double delta_t = std::stod(argv[2]);

    sf::RenderWindow window(sf::VideoMode(800, 600), "NBody Simulation");

    Universe universe;
    std::cin >> universe;

    // Set the initial view size to match the window size
    sf::View view;
    view.setSize(800.0f, 600.0f);
    view.setCenter(400.0f, 300.0f);
    window.setView(view);

    // to draw a bunch of stars
    sf::Texture star;
    if (!star.loadFromFile("assets/star.gif"))
        return 1;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // flicker rate
    sf::Clock flicker;
    sf::Time flickerTime = sf::seconds(1.0f);

    // 3 different sets of stars in different positions and flickering rates
    std::vector<sf::Vector2f> position1_3, position2_3, position3_3;
    std::vector<float> starsFlick1_3, starsFlick2_3, starsFlick3_3;

    // 1/3 of the stars
    for (int i = 0; i < 20; i++) {
        float x = static_cast<float>(std::rand() % window.getSize().x);
        float y = static_cast<float>(std::rand() % window.getSize().y);
        position1_3.push_back(sf::Vector2f(x, y));
        starsFlick1_3.push_back(200.0f);
    }

    // 2/3 of the stars
    for (int i = 0; i < 20; i++) {
        float x = static_cast<float>(std::rand() % window.getSize().x);
        float y = static_cast<float>(std::rand() % window.getSize().y);
        position2_3.push_back(sf::Vector2f(x, y));
        starsFlick2_3.push_back(255.0f);
    }

    // 3/3 of the stars
    for (int i = 0; i < 20; i++) {
        float x = static_cast<float>(std::rand() % window.getSize().x);
        float y = static_cast<float>(std::rand() % window.getSize().y);
        position3_3.push_back(sf::Vector2f(x, y));
        // full visibility
        starsFlick3_3.push_back(255.0f);
    }

    // elapse time on screen, font
    sf::Font font;
    if (!font.loadFromFile("Manjari-Bold.otf"))
        return 1;

    sf::Text elapsedText;
    elapsedText.setFont(font);
    elapsedText.setCharacterSize(20);
    elapsedText.setFillColor(sf::Color::Red);
    elapsedText.setPosition(550.0f, 10.0f);

    double elapsedTime = 0.0;

    // sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("soundsOfSpace.ogg"))
        return 1;

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    while (window.isOpen() && elapsedTime < T) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        universe.step(delta_t);

        // for text
        elapsedTime += delta_t;
        elapsedText.setString(std::to_string(elapsedTime) + " secs");
        // Clear the window
        window.clear();
        // Draw the text
        window.draw(elapsedText);

        // draw multiple copies of star.gif
        for (unsigned int i = 0; i < position1_3.size(); i++) {
            // three different sets
            sf::Sprite starSprite1(star);
            sf::Sprite starSprite2(star);
            sf::Sprite starSprite3(star);

            starSprite1.setPosition(position1_3[i]);
            starSprite2.setPosition(position2_3[i]);
            starSprite3.setPosition(position3_3[i]);

            float alphaCal1 = 128.0f + 127.0f * sin(2 * 3.1415 *
                            flicker.getElapsedTime().asSeconds()
                            / flickerTime.asSeconds());

            float alphaCal2 = 128.0f + 127.0f * sin(3.1415 *
                            flicker.getElapsedTime().asSeconds()
                            / flickerTime.asSeconds());

            starSprite1.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alphaCal1)));
            starSprite2.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alphaCal2)));

            window.draw(starSprite1);
            window.draw(starSprite2);
            window.draw(starSprite3);
        }

        // Get the celestial bodies and draw
        for (CelestialBody &body : universe.getBodies()) {
            body.update(delta_t, universe.getBodies());
            window.draw(body);
        }

        // Display everything on the screen
        window.display();
    }

    std::cout << universe << std::endl;

    return 0;
}
