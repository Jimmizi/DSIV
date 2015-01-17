#include "map.h"
#include <fstream>

Map::Map(int newLevel)
{
    //setting values for the rawMap to 0
    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            rawMap[x][y] = "0";
        }
    }

    //setting up the grid coordinate system
    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            coordinates[x][y].x = x * 32;
            coordinates[x][y].y = y * 32;
        }
    }

    //defaulting all position in use to free
    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            positionsInUse[x][y] = false;
        }
    }

    //Texture loadind
    grassTexture.loadFromFile("textures/grass.png");
    pathTexture.loadFromFile("textures/path.png");

    level = newLevel;
}

Map::~Map()
{

}


bool Map::loadLevel()
{
    std::string txt[200];
    std::string line;

    int i=0;
    std::ifstream file;

    switch(level)
    {
    case 1:
        file.open("maps/map.txt");
        break;
    case 2:
        file.open("maps/map2.txt");
        break;
    case 3:
        file.open("maps/map3.txt");
        break;
    case 4:
        file.open("maps/map4.txt");
        break;
    case 5:
        file.open("maps/map5.txt");
        break;
    case 6:
        file.open("maps/map6.txt");
        break;
    default:
        std::cout << "\n\nUnable to load 'map " << level << "'.";
        std::cout << "\nPlease check the level files.";
        sf::sleep(sf::seconds(1));
        std::cout << "\n\nAborting game...";
        sf::sleep(sf::seconds(0.5));
        return false;
    }

    if (file.is_open())
    {
        while (!file.eof())
        {
            std::getline(file,line);
            txt[i]=line;
            i++;
        }
    }

    file.close();

    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            rawMap[x][y] = txt[y].at(x);

            if(rawMap[x][y] == "0")
            {
                mapSprites[x][y].setTexture(grassTexture);
            }
            else if(rawMap[x][y] != "0")
            {
                mapSprites[x][y].setTexture(pathTexture);
            }

            if(rawMap[x][y] != "0")
            {
                positionsInUse[x][y] = true;
            }
        }
    }

    //setting the sprites to the coordinates
    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            mapSprites[x][y].setPosition(coordinates[x][y]);
        }
    }

    return true;
}

void Map::draw(sf::RenderWindow &window)
{
    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            window.draw(mapSprites[x][y]);
        }
    }
}

bool Map::spaceUsed(sf::Vector2i mousePosition)
{
    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        {
            if(mousePosition.x > coordinates[x][y].x && mousePosition.x < coordinates[x][y].x + 33 &&
               mousePosition.y > coordinates[x][y].y && mousePosition.y < coordinates[x][y].y + 33)
            {
                if(positionsInUse[x][y])
                    return true;
                else return false;
            }
        }
    }
}




