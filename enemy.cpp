#include "enemy.h"

Enemy::Enemy()
{
    texture.loadFromFile("textures/enemy1.png");

    int randomSpeed = rand() % 3;
    health = rand() % 40 + 90;

    if(randomSpeed == 0)
    {
        speed = 0.5;
        health += 50;
    }
    else if(randomSpeed == 1)
    {
        speed = 1;
        health +=20;
    }
    else if(randomSpeed == 2)
    {
        speed = 2;
    }




	worth = rand() % 5;

    object.setTexture(texture);
    object.setTextureRect(sf::IntRect(0, 0, 32, 32));

    int state = 0;
    for(int y = 0; y < 2; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            animationState[state] = sf::IntRect(x*32, y*32, 32, 32);
            state++;
        }
    }

    lastState = 6;

    for(int i = 0; i < 20; i++)
    {
        actionsTaken[i] = false;
        moves[i] = 0;
    }
}

Enemy::~Enemy()
{

}

void Enemy::loadPath(std::string rawMap[32][24], bool enemyQueue[1000])
{
    bool stillLoading = true;

    //used to store the current coordinates that we're searching
    int currentY = 0;
    int currentX = 0;

    for(int x = 0; x < 32; x++)
    {
        if(rawMap[x][currentY] == "4") //getting the start
        {
            //checking to see where it is in the wave queue
            for(int pos = 0; pos < 1000; pos++)
            {
                if(!enemyQueue[pos])
                {
                    enemyQueue[pos] = true;
                    object.setPosition(sf::Vector2f(x*32,-32*pos));

                    tempActions[0].y += 32*pos;

                    break;
                }
            }

            //after finding start, count how many down it will go
            for(int down = 1; rawMap[x][down] == "5"; down++)
            {
                currentX = x;
                currentY = down;
                tempActions[0].y += 32;
            }

            int action = 0;

            while(stillLoading)
            {
                //testing to see whether left or right
                if(rawMap[currentX+1][currentY] == "5")
                {
                    int tempX = 0;
                    for(int right = 1; rawMap[currentX + right][currentY] == "5"; right++)
                    {
                        tempActions[action].x += 32;
                        tempX = right;
                    }

                    currentX += tempX;
                }
                else if(rawMap[currentX-1][currentY] == "5")
                {
                    int tempX = 0;
                    for(int left = 1; rawMap[currentX - left][currentY] == "5"; left++)
                    {
                        tempActions[action].x -= 32;
                        tempX = left;
                    }
                    currentX -= tempX;
                }

                action++;

                //testing to see whether up and down
                if(rawMap[currentX][currentY+1] == "5")
                {
                    int tempY = 0;
                    for(int down = 1; rawMap[currentX][currentY + down] == "5"; down++)
                    {
                        tempActions[action].y += 32;
                        tempY = down;
                    }

                    currentY += tempY;
                }
                else if(rawMap[currentX][currentY-1] == "5")
                {
                    int tempY = 0;
                    for(int up = 1; rawMap[currentX][currentY - up] == "5"; up++)
                    {
                        tempActions[action].y -= 32;
                        tempY = up;
                    }
                    currentY -= tempY;
                }

                if(rawMap[currentX+1][currentY] == "6")
                {
                    tempActions[action].x += 64;
                    stillLoading = false;
                }
                else if(rawMap[currentX][currentY+1] == "6")
                {
                    tempActions[action].y += 64;
                    stillLoading = false;
                }
            }

            //Assigning path to the proper variable
            int I = 0;
            for(int i = 0; i < 20; i+=2)
            {
                moves[i] = tempActions[I].y;
                I++;
            }
            I = 0;
            for(int i = 1; i < 21; i+=2)
            {
                moves[i] = tempActions[I].x;
                I++;
            }
        }
    }
}

bool Enemy::update(sf::Time dt, sf::Clock &clock)
{
    if(dt.asSeconds() > 0.25)
    {
        int state;

        switch(lastState)
        {
        case 0:
            state = 1;
            break;
        case 1:
            state = 2;
            break;
        case 2:
            state = 3;
            break;
        case 3:
            state = 4;
            break;
        case 4:
            state = 5;
            break;
        case 5:
            state = 0;
            break;
        default:
            state = 0;
            break;
        }

        object.setTextureRect(animationState[state]);
        lastState = state;
        clock.restart();
    }

    for(int test = 0; test < 20; test++)
    {
        if(!actionsTaken[test])
        {
            if(test % 2 == 0) //if y movement
            {
                if(moves[test] < 0 || moves[test] > 0)
                {
                    if(moves[test] > 0)
                    {
                        object.move(0,speed);
                        moves[test] -= speed;
                    }
                    else if(moves[test] < 0)
                    {
                        object.move(0,-speed);
                        moves[test] +=speed;
                    }
                }
                else
                {
                    actionsTaken[test] = true;
                }
            }

            if(test % 2 == 1) //if x movement
            {
                if(moves[test] < 0 || moves[test] > 0)
                {
                    if(moves[test] > 0)
                    {
                        object.move(speed,0);
                        moves[test] -= speed;
                    }
                    else if(moves[test] < 0)
                    {
                        object.move(-speed,0);
                        moves[test] += speed;
                    }
                }
                else
                {
                    actionsTaken[test] = true;
                }
            }

            return true;
        }


    }

    return false;
}

void Enemy::enemyType()
{

}

void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(object);
    return;
}

int Enemy::getCurrentAction()
{
    for(int i = 0; i < 20; i++)
    {
        if(!actionsTaken[i])
            return i+1;
    }
}

