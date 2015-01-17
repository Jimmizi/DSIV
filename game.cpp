#include "GameObject.cpp"
#include "Map.cpp"
#include "System.h"
#include "tower.cpp"
#include "enemy.cpp"

#include <iostream>

bool game(sf::RenderWindow &window, System &system, int level)
{
    if(level == -1)
        return false;

	///MISCELLANEOUS VARIABLES START

    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    sf::Event event;

	int lives = 6;
	int wave = 1;
	int gold = 300;

	int towerToPlace = 0;

    //Used to store the last mouse press for both left clicking and right clicking
    bool lastClick[2] = { false, false } ;

    //clock and time var for animation
    sf::Clock clockAnim;
    sf::Time dtAnim = clockAnim.getElapsedTime();

    sf::Clock clockBuy;
    sf::Time dtBuy = clockBuy.getElapsedTime();

    sf::Clock clock;
    sf::Time dt = clock.getElapsedTime();

    //clock and time var for turret firing
    sf::Clock clockTurr;
    sf::Time dtTurr = clockTurr.getElapsedTime();

    ///MISCELLANEOUS VARIABLES END


    ///MUSIC INITILIZATION START

    sf::Music gameMusic[10];

    for(int i = 0; i < 3; i++)
    {
        gameMusic[i].openFromFile("music/dM - A Starting Point.ogg");
    }

    for(int i = 3; i < 6; i++)
    {
        gameMusic[i].openFromFile("music/dM - Speed.ogg");
    }

    for(int i = 6; i < 10; i++)
    {
        gameMusic[i].openFromFile("music/dM - Downhill.ogg");
    }

    int currentTrack = rand() % 10;
    std::vector<int> previousTracks;

    previousTracks.push_back(currentTrack);

    ///MUSIC INITILIZATION END


    ///MAP INITILIZATION START


    Map map(level);

    if(map.loadLevel())
        std::cout << "Loaded level!\n";
    else
    {
        system.quit();
        return false;
    }

    ///MAP INITILIZATION START


    ///ENEMY INITILIZATION START

    bool enemyQueue[1000];
    bool enemyAlive[1000];

	int enemyAmount = 20;

	int enemyAliveInt = enemyAmount;

    Enemy* enemies;
    enemies = new Enemy[enemyAmount];

    for(int i = 0; i < enemyAmount; i++)
    {
        enemies[i].loadPath(map.rawMap, enemyQueue);
    }

    for(int i = 0; i < 1000; i++)
    {
        enemyAlive[i] = true;
        enemyQueue[i] = false;
    }

    ///ENEMY INITILIZATION END


    ///TOWER INITILIZATION START

    int towerCount = 0;

    //Used to tell when a certain tower is up
    std::vector<int> towerUp;

    for(int i = 0; i < 768; i++)
    {
        towerUp.push_back(0);
    }

    //vector of towers
    std::vector<Tower> towers;

    ///TOWER INITILIZATION END


    ///UI INITILIZATION START

    sf::Font font;
	font.loadFromFile("visitor.ttf");

	sf::RectangleShape rightPanel(sf::Vector2f(62,768));
	sf::Texture rightPanelTexture;
	sf::RectangleShape selectedTower[10];

	sf::RectangleShape descriptionBG[10];
	sf::Texture descriptionBGTexture;
	descriptionBGTexture.loadFromFile("textures/descriptionBox.png");

	sf::Text statsText[10];
	sf::Text descriptionStatsText[10];


	/*features things like: current wave, gold, tower descriptions etc
		UI_Text
		[0] = CURRENT WAVE
		[1] = GOLD
		[2] = LIVES
		[3] = ENEMIES STILL ALIVE

		towerUI_Textures && towerUI_Sprites
		[0] = STAR TOWER

	*/
	sf::Text UI_Text[20];
	Tower UI_Towers[10];

	for(int i = 0; i < 10; i++)
	{
		UI_Towers[i].setPosition(sf::Vector2f(1049, 200 + (i * 39)));
		UI_Towers[i].setAsDummy();
		UI_Towers[i].textureNumber = 1;

		selectedTower[i].setSize(sf::Vector2f(68,38));
		selectedTower[i].setFillColor(sf::Color(255,255,255,125));
		selectedTower[i].setPosition(sf::Vector2f(1024, 197 + (i * 39)));

		descriptionBG[i].setSize(sf::Vector2f(200,200));
		descriptionBG[i].setPosition(sf::Vector2f(814, 116 + (i * 39)));
		descriptionBG[i].setTexture(&descriptionBGTexture);

		statsText[i].setFont(font);
		statsText[i].setCharacterSize(16);
		statsText[i].setColor(sf::Color::White);
		statsText[i].setPosition(sf::Vector2f(824, 120 + (i * 39)));
		statsText[i].setString(UI_Towers[i].getDescription(i));
	}

	//Current wave
	UI_Text[0].setColor(sf::Color(sf::Color::White));
	UI_Text[0].setPosition(sf::Vector2f(1029,5));
	UI_Text[0].setString(system.convertInt(wave));

	//Gold
	UI_Text[1].setColor(sf::Color(sf::Color(255,201,14,255)));
	UI_Text[1].setPosition(sf::Vector2f(1029,47)); //minus 20 off PS to get this
	UI_Text[1].setString(system.convertInt(gold));

	//Lives
	UI_Text[2].setColor(sf::Color(sf::Color(251,85,206,255)));
	UI_Text[2].setPosition(sf::Vector2f(1029,98));
	UI_Text[2].setString(system.convertInt(lives));

    //Enemies left
	UI_Text[3].setColor(sf::Color(sf::Color::White));
	UI_Text[3].setPosition(sf::Vector2f(1029,150));
	UI_Text[3].setString(system.convertInt(enemyAliveInt));


	for(int i = 0; i < 20; i++)
    {
        UI_Text[i].setFont(font);
    }

	rightPanelTexture.loadFromFile("textures/rightPanel.png");
	rightPanel.setPosition(sf::Vector2f(1024,0));
	rightPanel.setTexture(&rightPanelTexture);


	///UI INITILIZATION END


    ///MAIN LOOP START
    ///-------------------------------------------------------------------------------------------------------------------

    gameMusic[currentTrack].play();

    while (window.isOpen())
    {
        ///UPDATES START

        localPosition = sf::Mouse::getPosition(window);
        dtAnim = clockAnim.getElapsedTime();
        dtTurr = clockTurr.getElapsedTime();
        dtBuy = clockBuy.getElapsedTime();
        dt = clock.getElapsedTime();

        UI_Text[0].setString(system.convertInt(wave));
        UI_Text[1].setString(system.convertInt(gold));
        UI_Text[2].setString(system.convertInt(lives));
        UI_Text[3].setString(system.convertInt(enemyAliveInt));

        UI_Towers[0].refreshTextures();

		///UPDATES END


		///WAVE LOGIC START

		if(lives < 0)
        {
            std::cout << "\n\nRan of of lives :(";
            delete[] enemies;

            system.quit();
            return false;
        }

		if(enemyAliveInt == 0)
		{
			//increase the wave by 10
			enemyAmount += 10;

			enemyAliveInt = enemyAmount;

			wave++;
			gold += 50;

			enemies = new Enemy[enemyAmount];

			for(int i = 0; i < 1000; i++)
			{
				enemyAlive[i] = true;
				enemyQueue[i] = false;
			}

			for(int i = 0; i < enemyAmount; i++)
			{
				enemies[i].loadPath(map.rawMap, enemyQueue);
			}
		}

		///WAVE LOGIC END


        ///GET DEVICE INPUT START

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                delete[] enemies;

                system.quit();
                return false;
            }

			//logic for buying a tower
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1 && towerToPlace != 1)
			{
                //place a starTower
                towerToPlace = 1;
                clockBuy.restart();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1 && dtBuy.asSeconds() > 0.2)
			{
                towerToPlace = 0;
			}

            //logic for adding a tower
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lastClick[0] && towerToPlace == 1)
                {
                    lastClick[0] = true;
                    if(!map.spaceUsed(localPosition) && gold > UI_Towers[0].getBuyAmount() - 1)
                    {
                        for(int i = 0; i < towerCount + 1; i++)
                        {
                            if(towerUp[i] == 0)
                            {
                                towerUp[i] = 1;
                                towerCount += 1;

                                Tower newTower;
                                newTower.place(map.coordinates, map.positionsInUse, localPosition);

                                towers.push_back(newTower);
                                towers[i].textureNumber = 1;

                                //Dirty fix for null references to textures after inserting/deleting towers
                                for(int tex = 0; tex < towerCount; tex++)
                                {
                                    towers[tex].refreshTextures();
                                }

                                towers[i].update();

								gold -= 125;

                                break;
                            }
                        }
                    }
                }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                lastClick[0] = false;

            //logic for removing a tower
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !lastClick[1])
                {
                    lastClick[1] = true;

                    for(int i = 0; i < towerCount; i++)
                    {
                        //if the tower is at the mouse's position
                        sf::FloatRect temp = towers[i].getBoundingBox();

                        if(temp.contains(localPosition.x, localPosition.y))
                        {
                            gold += towers[i].getSellAmount();
                            towers[i].deleteTower(map.positionsInUse);
                            towerUp.erase(towerUp.begin() + i);
                            towerCount -= 1;
                            towers.erase(towers.begin() + i);

                            for(int tex = 0; tex < towerCount; tex++)
                            {
                                towers[tex].refreshTextures();
                            }
                            break;
                        }
                    }
                }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
                lastClick[1] = false;

        }

        ///GET DEVICE INPUT END

        ///MUSIC LOGIC START

        if(gameMusic[currentTrack].getStatus() == sf::SoundSource::Stopped)
        {
            for(int i = 0; i < previousTracks.max_size(); i++)
            {
                if(previousTracks[i] == currentTrack)
                {
                    currentTrack = rand() % 10 + 1;
                    i = 0;
                }

                if(i > 5)
                    break;
            }

            previousTracks.push_back(currentTrack);
            gameMusic[currentTrack].play();
        }

        ///MUSIC LOGIC END


        /// TOWER UPDATE & LOGIC START

        window.clear();
        map.draw(window);

        //drawing the range of the tower underneath everything else
        for(int i = 0; i < towerCount; i++)
        {
            sf::FloatRect temp = towers[i].getBoundingBox();

            if(temp.contains(localPosition.x, localPosition.y))
                towers[i].drawRange = true;
            else
                towers[i].drawRange = false;

            if(towerUp[i] == 1)
            {
                if(towers[i].drawRange)
                    towers[i].drawTheRange(window);
            }
        }

        for(int i = 0; i < towerCount; i++)
        {
            if(towerUp[i] == 1)
            {
                towers[i].draw(window,true);
                towers[i].shoot(enemies,enemyAmount,dtTurr,clockTurr,window);
            }
        }

        /// TOWER UPDATE & LOGIC END


        /// ENEMY UPDATE & LOGIC START

        //Enemy logic
        for(int i = 0; i < enemyAmount; i++)
        {
            //deleting enemy if killed
            if(enemies[i].health <= 0 && enemyAlive[i])
            {
				gold += enemies[i].getWorth();
                delete &enemies[i];
                enemyAlive[i] = false;

                enemyAliveInt--;
            }

            //deleting enemy if end of path & decrementing lives
            if(!enemies[i].update(dtAnim,clockAnim) && enemyAlive[i])
            {
                delete &enemies[i];
                enemyAlive[i] = false;
                lives--;
                enemyAliveInt--;
            }

            if(enemyAlive[i])
                enemies[i].draw(window);
        }

        /// ENEMY UPDATE & LOGIC END


        ///UI DRAWING START

		window.draw(rightPanel);

		for(int i = 0; i < 4; i++)
		{
			window.draw(UI_Text[i]);
		}

		for(int i = 0; i < 10; i++)
		{
            if(towerToPlace == i+1)
            {
                window.draw(selectedTower[i]);
                window.draw(descriptionBG[i]);
                window.draw(statsText[i]);
            }

			UI_Towers[i].draw(window,true);
		}

		///UI DRAWING END

        window.display();
    }

    return false;
}
