#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void draw(sf::RenderWindow &window);

    void setPosition(sf::Vector2f newPos);
    sf::Vector2f getPosition();

    sf::Texture getTexture();
    void setTexture(sf::Texture &newTexture);

    sf::Sprite getSprite();

    bool collide(sf::FloatRect &otherObject);

    int objectCount();

    void setBoundingBox();
    sf::FloatRect getBoundingBox();

    void update();

protected:
    sf::Texture texture;
    sf::Sprite object;

    sf::Vector2i positionCoords;

    sf::FloatRect boundingBox;

    static int gameObjectCount;

};

#endif // GAMEOBJECT_H
