#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <time.h>
#include "testheader.h"

int main()
{
    sf::Time dt;
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "test", sf::Style::Close);
    window.setFramerateLimit(60);

    sf::RectangleShape player;
    player.setSize(sf::Vector2f(32,32));
    player.setPosition(400,300);
    player.setFillColor(sf::Color::Red);

    sf::FloatRect leftBB(0,0,10,28);
    sf::RectangleShape leftObj;
    leftObj.setSize(sf::Vector2f(10,28));

    sf::FloatRect rightBB(0,0,10,28);
    sf::RectangleShape rightObj;
    rightObj.setSize(sf::Vector2f(10,28));

    sf::FloatRect upBB(0,0,28,10);
    sf::RectangleShape upObj;
    upObj.setSize(sf::Vector2f(28,10));

    sf::FloatRect downBB(0,0,28,10);
    sf::RectangleShape downObj;
    downObj.setSize(sf::Vector2f(28,10));


    sf::RectangleShape obstacle;
    sf::FloatRect obstacleBB(100,100,48,300);

    obstacle.setPosition(100,100);
    obstacle.setSize(sf::Vector2f(48,300));

    obstacleBB = obstacle.getGlobalBounds();

    bool blockedLeft = false;
    bool blockedRight = false;
    bool blockedUp = false;
    bool blockedDown = false;

    while(true)
    {
        dt = clock.getElapsedTime();
        leftBB = leftObj.getGlobalBounds();
        rightBB = rightObj.getGlobalBounds();
        upBB = upObj.getGlobalBounds();
        downBB = downObj.getGlobalBounds();

        leftObj.setPosition(player.getPosition().x - 10,player.getPosition().y + 2);
        rightObj.setPosition(player.getPosition().x + 32,player.getPosition().y + 2);

        upObj.setPosition(player.getPosition().x + 2,player.getPosition().y -10);
        downObj.setPosition(player.getPosition().x + 2,player.getPosition().y + 32);

        blockedLeft = leftBB.intersects(obstacleBB) ? true : false;
        blockedRight = rightBB.intersects(obstacleBB) ? true : false;
        blockedUp = upBB.intersects(obstacleBB) ? true : false;
        blockedDown = downBB.intersects(obstacleBB) ? true : false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !blockedLeft)
        {
            player.move(-2,0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !blockedRight)
        {
            player.move(2,0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !blockedUp)
        {
            player.move(0,-2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !blockedDown)
        {
            player.move(0,2);
        }

        window.clear();
        window.draw(player);
        window.draw(obstacle);
        window.display();
    }
}







