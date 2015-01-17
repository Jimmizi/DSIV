#include "tower.h"
#include <math.h>
#define PI 3.1415926535

#include "collision.cpp"
#include <sstream>

//constructor

Tower::Tower()
{
    range = 4;
	towerCost = 125;
	sellAmount = 75;
    targetFirst = true;
    hasTarget = false;
    drawRange = false;
    firing = false;
	isDummy = false;

    projectileTexture.setRepeated(false);

    pauseBetweenFires = 0.55;
    damage = 25;
    bulletCount = 1;

    positionCoords.x = 0;
    positionCoords.y = 0;
}

Tower::~Tower()
{

}

void Tower::setAsDummy()
{
	isDummy = true;

	return;
}

void Tower::shoot(Enemy *enemies, int enemyAmount, sf::Time &dt, sf::Clock &clock, sf::RenderWindow &window)
{
	if(!isDummy)
	{
        if(!hasTarget)
        {
            for(int i = 0; i < enemyAmount; i++)
            {
                //Checking for new target if no target. Checks against health and if first enemy is alive
                if(enemies[i].collide(rangeBB) && enemies[i].health > 0 && !hasTarget)
                {
                    if(targetFirst)
                    {
                        target = i;
                        break;
                        //hasTarget = true;

                        //tempPosition = enemies[target].getPosition();
                    }
                }
            }

            //recheck to see if there's another enemy but faster and further down the path
            for(int i = 0; i < enemyAmount; i++)
            {
                if(enemies[i].collide(rangeBB) && enemies[i].health > 0 && !hasTarget)
                {
                    if(enemies[target].getCurrentAction() <= enemies[i].getCurrentAction())
                    {
                        if(enemies[target].getSpeed() < enemies[i].getSpeed())
                        {
                            target = i;
                        }
                    }
                }
            }

            hasTarget = true;
            tempPosition = enemies[target].getPosition();
        }

        if(targetFirst)
        {
            for(int i = 0; i < enemyAmount; i++)
            {
                if(enemies[i].collide(rangeBB) && enemies[i].health > 0)
                {
                    if(enemies[target].getCurrentAction() < enemies[i].getCurrentAction())
                    {
                        target = i;
                    }
                }
            }
        }

		//clearing the target if enemy has been killed
		if(hasTarget && enemies[target].health <= 0)
		{
			target = NULL;
			hasTarget = false;
		}

		//damaging the enemy if still in range and alive
		else if(enemies[target].collide(rangeBB) && hasTarget && enemies[target].health > 0)
		{
			// code to get the tower to set it's rotation dependant on the current target
			object.setRotation(((1* 360 / PI * (atan2(static_cast<double>(object.getPosition().y - enemies[target].getPosition().y - 16),
													  static_cast<double>(object.getPosition().x - enemies[target].getPosition().x - 16))))/2)+90);

			projectileSprite.setRotation(object.getRotation());

			sf::Vector2f scaleFactor = object.getPosition() - enemies[target].getPosition();


			if(firing)
			{
				if(target != NULL)
					endPosition = sf::Vector2f(enemies[target].getPosition().x + 16 - object.getPosition().x,
											   enemies[target].getPosition().y + 16 - object.getPosition().y);
				else if(target == NULL)
					endPosition = sf::Vector2f(tempPosition.x + 16 - object.getPosition().x,
											   tempPosition.y + 16 - object.getPosition().y);


				if(dt.asSeconds() > 0.03 && dt.asSeconds() < 0.06)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.1,
												 object.getPosition().y + endPosition.y * 0.1);

				else if(dt.asSeconds() > 0.06 && dt.asSeconds() < 0.09)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.2,
												 object.getPosition().y + endPosition.y * 0.2);

				else if(dt.asSeconds() > 0.09  && dt.asSeconds() < 0.12)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.3,
												 object.getPosition().y + endPosition.y * 0.3);

				else if(dt.asSeconds() > 0.12 && dt.asSeconds() < 0.15)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.4,
												 object.getPosition().y + endPosition.y * 0.4);

				else if(dt.asSeconds() > 0.15 && dt.asSeconds() < 0.18)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.5,
												 object.getPosition().y + endPosition.y * 0.5);

				else if(dt.asSeconds() > 0.18 && dt.asSeconds() < 0.21)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.6,
												 object.getPosition().y + endPosition.y * 0.6);

				else if(dt.asSeconds() > 0.21  && dt.asSeconds() < 0.24)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.7,
												 object.getPosition().y + endPosition.y * 0.7);

				else if(dt.asSeconds() > 0.24 && dt.asSeconds() < 0.27)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.8,
												 object.getPosition().y + endPosition.y * 0.8);

				else if(dt.asSeconds() > 0.27 && dt.asSeconds() < 0.30)
					projectileSprite.setPosition(object.getPosition().x + endPosition.x * 0.9,
												 object.getPosition().y + endPosition.y * 0.9);

				else if(dt.asSeconds() > 0.30)
				{
					projectileSprite.setPosition(object.getPosition().x + endPosition.x,
												 object.getPosition().y + endPosition.y);
					firing = false;
					projectileSprite.setPosition(object.getPosition());
				}

				if(firing)
					window.draw(projectileSprite);
			}

			//Calculating how many shots will be taken by rate of fire & bulletCount
			if(dt.asSeconds() > pauseBetweenFires)//dt.asSeconds() < 0.1)
			{
				for(int shots = 0; shots < bulletCount; shots++)
				{
					tempPosition = enemies[target].getPosition();
					enemies[target].health -= damage;
					firing = true;
				}
				clock.restart();
			}
		}
		//else clearing the target if the enemy has left the range of the turret
		else if(!enemies[target].collide(rangeBB) && hasTarget)
		{
			tempPosition = enemies[target].getPosition();
			target = NULL;
			hasTarget = false;
		}
	}

    return;
}

void Tower::place(sf::Vector2f coordinates[32][24], bool positionsInUse[32][24], sf::Vector2i mousePosition)
{
	if(!isDummy)
	{
		for(int y = 0; y < 24; y++)
		{
			for(int x = 0; x < 32; x++)
			{
				if(mousePosition.x > coordinates[x][y].x && mousePosition.x < coordinates[x][y].x + 33 &&
				   mousePosition.y > coordinates[x][y].y && mousePosition.y < coordinates[x][y].y + 33)
				{
					if(positionsInUse[x][y] == false)
					{
						object.setPosition(coordinates[x][y]);

						object.setOrigin(16,16);
						towerBaseSprite.setOrigin(16,16);

						object.setPosition(coordinates[x][y].x + 16,coordinates[x][y].y + 16);
						towerBaseSprite.setPosition(coordinates[x][y].x + 16,coordinates[x][y].y + 16);

						projectileSprite.setOrigin(4,0);
						projectileSprite.setPosition(coordinates[x][y].x + 16,coordinates[x][y].y + 16);

						positionsInUse[x][y] = true;

						positionCoords.x = x;
						positionCoords.y = y;

						//will calculate based on the range and turret position
						rangeBB = sf::FloatRect(object.getPosition().x - 16 - range*32,
												object.getPosition().y - 16 - range*32,
												32* range*2 + 32,
												32* range*2 + 32);

						//setting the rangeShape to the size/position of the range bounding box
						rangeShape.setSize(sf::Vector2f(32* range*2 + 32, 32* range*2 + 32));

						rangeShape.setPosition(object.getPosition().x - 16 - range*32,
											   object.getPosition().y - 16 - range*32);


						return;
					}
					else return;
				}
			}
		}
	}

    return;
}

void Tower::deleteTower(bool positionsInUse[32][24])
{
	if(!isDummy)
	{
		positionsInUse[positionCoords.x][positionCoords.y] = false;
		positionCoords.x = 0;
		positionCoords.y = 0;
	}

    return;
}

void Tower::drawTheRange(sf::RenderWindow &window)
{
    if(drawRange && !isDummy)
        window.draw(rangeShape);

    return;
}

void Tower::draw(sf::RenderWindow &window, bool use)
{
    if(!isDummy)
        window.draw(towerBaseSprite);

	window.draw(object);

	return;
}

void Tower::refreshTextures()
{
    switch(textureNumber)
    {
    case 1:
        texture.loadFromFile("textures/startower.png");
        towerBaseTexture.loadFromFile("textures/startower_base.png");
        break;
    }

    towerBaseSprite.setTexture(towerBaseTexture);

    projectileTexture.loadFromFile("textures/bullets.png");
    projectileSprite.setTexture(projectileTexture, false);

    rangeTexture.loadFromFile("textures/range.png");
    rangeShape.setTexture(&rangeTexture);

    object.setTexture(texture);

    return;
}

std::string Tower::getDescription(int tower)
{
    std::string toReturn;

    if(tower == 0)
    {
        std::stringstream ss;
        std::stringstream ss2;
        std::stringstream ss3;
        std::stringstream ss4;

        toReturn.append("Buy: ");

        ss << towerCost;
        toReturn.append(ss.str());
        toReturn.append("\nSell: ");

        ss2 << sellAmount;
        toReturn.append(ss2.str());
        toReturn.append("\nRate of fire: ");

        ss3 << pauseBetweenFires;
        toReturn.append(ss3.str());
        toReturn.append("\nDamage: ");

        ss4 << damage;
        toReturn.append(ss4.str());

        toReturn.append("\n\nStar Tower: The basic tower\nin DSIV. Doesn't do any\nspecial damage towards\nred/blue enemies. Most basic\nof the towers.");
    }

    return toReturn;
}





