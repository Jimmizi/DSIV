#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject
{
public:
    Enemy();
    ~Enemy();

    void loadPath(std::string rawMap[32][24], bool enemyQueue[1000]);

    //Should only be called once
    //void initialiseQueue();

    //returns whether the enemy still has to update or not
    bool update(sf::Time dt, sf::Clock &clock);
    void enemyType();

    void draw(sf::RenderWindow &window);

	int getWorth() { return worth; }
	int getCurrentAction();
	float getSpeed() { return speed; }

    int health;

private:
    static int enemyCount;

    //needs to be something of the following: 0.175, 0.25, 0.5, 1, 2, 4, 8, 16, 32, 64
    float speed;

    //how much money and experience you receive from each enemy
    int worth;
    int experience;

    // If in future certain enemy types will attack towers
    int damage;

    std::string type;

    //used to store the paths the enemy will go along
    sf::Vector2f tempActions[10];

    //stores the moves. if going down, first move will be y then x then y etc.
    float moves[20];
    bool actionsTaken[20];


    //animation states
    sf::IntRect animationState[6];
    int lastState;

};

#endif // ENEMY_H
