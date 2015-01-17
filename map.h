#ifndef MAP_H
#define MAP_H

#include <iostream>

class Map
{
public:
    Map(int newLevel);
    ~Map();

    //returns if the map loaded correctly or not
    bool loadLevel();

    void draw(sf::RenderWindow &window);

    std::string rawMap[32][24];

    bool positionsInUse[32][24];
    sf::Vector2f coordinates[32][24];

    bool spaceUsed(sf::Vector2i mousePosition);

private:
    int level;

    //Array of sprites to draw as the background
    sf::Sprite mapSprites[32][24];

    sf::Texture pathTexture;
    sf::Texture grassTexture;


};

#endif // MAP_H
