#include "GameObject.h"
#include <iostream>

void GameObject::addComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

void GameObject::update() {
    for (auto& comp : components) {
        comp->update();
    }
}

void GameObject::setVelocity(float newVelocity)
{
    velocity = newVelocity;
}

void GameObject::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
}

void GameObject::setDirectin(sf::Vector2f newDirection)
{
    direction = newDirection;
}