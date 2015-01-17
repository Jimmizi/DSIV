#ifndef TOWER_H
#define TOWER_H

#include "GameObject.h"
#include "enemy.h"

class Tower : public GameObject
{
public:

    Tower();
    ~Tower();

	//To set the tower as a dummy for the UI drawing
	void setAsDummy();

    void shoot(Enemy *enemies, int enemyAmount, sf::Time &dt, sf::Clock &clock, sf::RenderWindow &window);

    void place(sf::Vector2f coordinates[32][24], bool positionsInUse[32][24], sf::Vector2i mousePosition);
    void deleteTower(bool positionsInUse[32][24]);

    bool drawRange;
    void drawTheRange(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window, bool use);

    void refreshTextures();

    //Used to store the texture that it will need to reload
    int textureNumber;

    sf::Vector2f tempPosition;

	int getBuyAmount() { return towerCost; }
	int getSellAmount() { return sellAmount; }

	std::string getDescription(int tower);

private:
    //Used as a collision bounding box
    sf::FloatRect rangeBB;

    //used to show the range of the turret
    sf::RectangleShape rangeShape;
    sf::Sprite projectileSprite;
	sf::Sprite towerBaseSprite;

    sf::Texture rangeTexture;
	sf::Texture towerBaseTexture;
    sf::Texture projectileTexture;

    //used to determine when the gun is being fired
    bool firing;

    //Position that the bullet should end up in
    sf::Vector2f endPosition;


    //to be implemented later - enemies that can damage turrets as they go past
    //float health;

    //damage of tower bullets
    float damage;

    //rate of fire in seconds. lower rate = faster, higher is slower
    float pauseBetweenFires;

    //number of tower bullets (from turrets)
    //generally the more bullets the less damage per bullet
    int bulletCount;

    int towerCost;
    int sellAmount;

    //used to help calculate how big the rangeBB will be
    int range;

    //the turrets level will affect stats
    int level;

    //gained after each enemy kill
    int experience;

    //methods of picking a target
    bool targetWeakest;
    bool targetStrongest;
    bool targetFirst;
    bool targetLast;

    //Whether the turret should put priority on the first or second lane
    //If on the first lane, turret won't deal damage to the second lane
    //unless the turret has AOE damage or AOE slowing
    bool prioritiseFirstLane;

    //integer used to store the current target.
    //bool used for a switch to know when and when not to assign a target
    int target;
    bool hasTarget;

	bool isDummy;
};

#endif // TOWER_H
