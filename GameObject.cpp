#include "GameObject.h"

GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}

void GameObject::draw(sf::RenderWindow &window)
{
    window.draw(object);
    return;
}

void GameObject::setPosition(sf::Vector2f newPos)
{
    object.setPosition(newPos);
    return;
}
sf::Vector2f GameObject::getPosition()
{
    return object.getPosition();
}

sf::Texture GameObject::getTexture()
{
    return texture;
}
void GameObject::setTexture(sf::Texture &newTexture)
{
    texture = newTexture;
    object.setTexture(texture);
    return;
}




sf::Sprite GameObject::getSprite()
{
    return object;
}


bool GameObject::collide(sf::FloatRect &otherObject)
{
    sf::FloatRect BB = object.getGlobalBounds();

    if(BB.intersects(otherObject))
        return true;
    else return false;
}

int GameObject::objectCount()
{

}

void GameObject::setBoundingBox()
{
    boundingBox = object.getGlobalBounds();
    return;
}

void GameObject::update()
{
    boundingBox = object.getGlobalBounds();
    return;
}

sf::FloatRect GameObject::getBoundingBox()
{
    return boundingBox;
}
