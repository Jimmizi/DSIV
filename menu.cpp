#include "Map.h"

using namespace std;

int menu(sf::RenderWindow &window)
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    int menu = 0;
    sf::Event event;

    Map map(2);
    map.loadLevel();

    //background texture

    sf::Texture MENUBGTEXTURE;
    MENUBGTEXTURE.loadFromFile("textures/menuBG.png");

    sf::RectangleShape logoBG(sf::Vector2f(1024,768));
    logoBG.setTexture(&MENUBGTEXTURE);

    //options border

    //border 1
    sf::RectangleShape optionBG(sf::Vector2f(300,300));
    optionBG.setPosition(0,200);
    optionBG.setTexture(&MENUBGTEXTURE);

    //border 2
    sf::RectangleShape levelBG(sf::Vector2f(650,650));
    levelBG.setPosition(320,200);
    levelBG.setTexture(&MENUBGTEXTURE);

    sf::Font font;
    if(!font.loadFromFile("visitor.ttf"))
        return 0;

    sf::Font titleFont;
    if(!titleFont.loadFromFile("dekapotmasss.ttf"))
        return 0;

    int fontSize = 42;
    sf::Color color = sf::Color::Red;
    sf::Color altColor = sf::Color::White;

    sf::Text title;
    title.setFont(titleFont);
    title.setCharacterSize(120);
    title.setColor(sf::Color(188,2,4));
    title.setPosition(25,25);
    title.setString("DIRTY Spatula in VEGAS");

    sf::Text option[5];
    sf::FloatRect boundingBox[5];
    for (int i = 0; i < 5; i++)
    {
        boundingBox[i] = option[i].getGlobalBounds();
        option[i].setFont(font);
        option[i].setCharacterSize(fontSize);
        option[i].setColor(color);
        option[i].setPosition(25,200 + (i * 50));
    }

    option[0].setString("Level Select");
    option[1].setString("Options");
    option[2].setString("About");
    option[3].setString("Tutorials");
    option[4].setString("Exit");

    //tutorial part
    sf::Texture tutorialTextures[4];
    sf::Sprite tutorialSprites[4];
    sf::RectangleShape arrows[2];
    sf::Texture arrowTextures[2];

    int currentTutorial = 1;

    tutorialTextures[0].loadFromFile("textures/tutorials/aboutTowerDefence.png");
    tutorialTextures[1].loadFromFile("textures/tutorials/sidebar.png");
    tutorialTextures[2].loadFromFile("textures/tutorials/howToPlace.png");
    tutorialTextures[3].loadFromFile("textures/tutorials/towersContinued.png");

    arrowTextures[0].loadFromFile("textures/tutorials/arrowLeft.png");
    arrowTextures[1].loadFromFile("textures/tutorials/arrowRight.png");

    arrows[0].setSize(sf::Vector2f(20,20));
    arrows[0].setTexture(&arrowTextures[0],true);
    arrows[1].setSize(sf::Vector2f(20,20));
    arrows[1].setTexture(&arrowTextures[1],true);

    arrows[0].setPosition(sf::Vector2f(500,170));
    arrows[1].setPosition(sf::Vector2f(750,170));

    sf::FloatRect arrowRightBB = arrows[1].getGlobalBounds();
    sf::FloatRect arrowLeftBB = arrows[0].getGlobalBounds();

    for(int i = 0; i < 4; i++)
    {
        tutorialSprites[i].setTexture(tutorialTextures[i], true);
        tutorialSprites[i].setPosition(sf::Vector2f(320,200));
    }

    bool states [5];

    states[0] = true;
    for (int i = 1; i < 5; i++)
    {
        states [i] = false;
    }

    //level select part
    sf::Text levelText[6];
    sf::FloatRect levelTextBB[6];

    levelText[0].setString("Level 1:");
    levelText[1].setString("Level 2:");
    levelText[2].setString("Level 3:");
    levelText[3].setString("Level 4:");
    levelText[4].setString("Level 5:");
    levelText[5].setString("Level 6:");

    int levelSelect = 1;

    for(int i = 0; i < 6; i++)
    {
        levelText[i].setCharacterSize(fontSize - 16);
        levelText[i].setFont(font);
        levelText[i].setColor(color);
        levelText[i].setPosition(340,200 + (i * 24));
    }

    //about screen
    sf::Text aboutText;

    aboutText.setColor(color);
    aboutText.setCharacterSize(fontSize - 16);
    aboutText.setPosition(340,200);
    aboutText.setFont(font);

    aboutText.setString("Created by datMoka and jb_summers94\n\n\n\n\nVersion: Alpha-2");

    bool lastClick = false;

    while(window.isOpen())
    {
        ///updates

        arrowRightBB = arrows[1].getGlobalBounds();
        arrowLeftBB = arrows[0].getGlobalBounds();

        localPosition = sf::Mouse::getPosition(window);
        for (int i = 0; i < 5; i++)
        {
             boundingBox[i] = option[i].getGlobalBounds();
        }

        for(int i = 0; i < 6; i++)
        {
            levelTextBB[i] = levelText[i].getGlobalBounds();
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return -1;

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return -1;

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lastClick)
                {
                    lastClick = true;

                    if(arrowLeftBB.contains(localPosition.x,localPosition.y) && states[3])
                    {
                        if(currentTutorial != 1)
                            currentTutorial--;
                    }
                    else if(arrowRightBB.contains(localPosition.x,localPosition.y) && states[3])
                    {
                        if(currentTutorial != 4)
                        currentTutorial++;
                    }

                    for(int y = 0; y < 5; y++)
                    {
                        if(boundingBox[y].contains(localPosition.x,localPosition.y))
                        {
                            for(int i = 0; i < 5; i++)
                            {
                                states[i] = false;
                            }

                            if(y == 4)
                                return -1;

                            states[y] = true;

                            if(!states[3])
                                currentTutorial = 1;
                        }
                    }

                    for(int i = 0; i < 6; i++)
                    {
                        if(levelTextBB[i].contains(localPosition.x,localPosition.y) && states[0])
                        {
                            return i + 1;
                        }
                    }
                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    lastClick = false;

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lastClick && states[0])
                {
                    lastClick = true;

                    for(int y = 0; y < 6; y++)
                    {
                        if(boundingBox[y].contains(localPosition.x,localPosition.y))
                        {
                            for(int i = 0; i < 6; i++)
                            {
                                states[y] = false;
                            }

                            states[menu + 1] = true;
                            return y + 1;
                        }
                    }
                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    lastClick = false;
            }

        for(int i = 0; i < 5; i++)
        {
            if(boundingBox[i].contains(localPosition.x, localPosition.y))
            {
                for(int reset = 0; reset < 5; reset++)
                {
                    option[reset].setColor(color);
                }

                option[i].setColor(altColor);
            }
        }

        for(int i = 0; i < 6; i++)
        {
            if(levelTextBB[i].contains(localPosition.x, localPosition.y))
            {
                for(int reset = 0; reset < 6; reset++)
                {
                    levelText[reset].setColor(color);
                }
                levelSelect = i + 1;
                levelText[i].setColor(altColor);
            }
        }

        window.clear();
        map.draw(window);
        window.draw(logoBG);
        window.draw(title);
        window.draw(optionBG);
        window.draw(levelBG);

        if(states[0])
        {
            for(int i = 0; i < 6; i++)
            {
                window.draw(levelText[i]);
            }
        }

        if(states[2])
            window.draw(aboutText);

        if(states[3])
        {
            window.draw(arrows[0]);
            window.draw(arrows[1]);
            window.draw(tutorialSprites[currentTutorial - 1]);
        }

        for(int i = 0; i < 5; i++)
            window.draw(option[i]);

        window.display();
    }


    return false;
}
