#include <iostream>
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "Paddle.h"
#include <sstream>

using namespace std;

int main()
{
    sf::VideoMode VM(1280, 720);
    sf::RenderWindow window(VM, "King Pong");
    sf::Clock clock;
    ball myball(1280 / 2, 3);
    Paddle myPaddle(1280 / 2, 710);

    sf::Font font;
    font.loadFromFile("fonts/Pixelemulator.otf");
    sf::Text fontHUD;
    fontHUD.setFont(font);
    fontHUD.setPosition(5, 0);
    fontHUD.setCharacterSize(30);
    fontHUD.setOutlineThickness(2);
    fontHUD.setOutlineColor(sf::Color::White);
    fontHUD.setFillColor(sf::Color::Magenta);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Magenta);
    gameOverText.setString("YOU ARE A LOSER!");
    gameOverText.setPosition(1280 / 2 - 200, 720 / 2 - 50);

    int lives = 3;
    std::stringstream ss;
    ss << "Lives: " << lives;
    fontHUD.setString(ss.str());

    sf::Time dt;
    sf::Event event;

    float bounceTimer = 0.10f;
    bool gameOver = false;

    while (window.isOpen()) {

        dt = clock.restart();
        bounceTimer -= dt.asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (gameOver) {
            
            window.clear();
            window.draw(gameOverText);
            window.display();
            sf::sleep(sf::seconds(3));
            window.close();
            continue;
        }

        if (myball.getPosition().intersects(myPaddle.getposition())) {
            if (bounceTimer < 0) {
                myball.hitball();
                bounceTimer = 0.10f;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            myPaddle.moveLeft();
        }
        else {
            myPaddle.stopLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            myPaddle.moveRight();
        }
        else {
            myPaddle.stopRight();
        }

        if (myball.getPosition().left < 0 || myball.getPosition().left + myball.getPosition().width > 1280) {
            myball.bounceSides();
        }

        if (myball.getPosition().top < 0 && bounceTimer < 0) {
            myball.bounceTop();
            bounceTimer = 0.10f;
        }

        if (myball.getPosition().top + myball.getPosition().height > 720) {
            myball.missBottom();
            lives--;
            ss.str("");
            ss << "Lives: " << lives;
            fontHUD.setString(ss.str());

            if (lives < 0) {
                gameOver = true;
            }
        }

        window.clear();
        myball.update(dt);
        myPaddle.update(dt);

        window.draw(myball.getShape());
        window.draw(myPaddle.getShape());
        window.draw(fontHUD);

        window.display();
    }

    return 0;
}
