#include "stdafx.h"
#include "MovementInputArrowsCP.h"
#include <iostream>

void MovementInputArrowsCP::update(float deltatime)
{
    processInput();
}

void MovementInputArrowsCP::processInput()
{
    if (!gameObject.expired())
    {
        std::shared_ptr<GameObject> go = gameObject.lock();
        std::shared_ptr<AnimatedGraphicsCP> aniGraphics = go->getComponentsOfType<AnimatedGraphicsCP>().at(0);
        std::shared_ptr<TransformationCP> transformation = go->getComponentsOfType<TransformationCP>().at(0);
        std::shared_ptr<RigidBodyCP> rigidBody = go->getComponentsOfType<RigidBodyCP>().at(0);

        transformation->setVelocity(0);

        if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Up))
        {
            aniGraphics->setAnimationType(Animationtype::RunUp);
            transformation->setDirection(sf::Vector2f(0, -1));
            transformation->setVelocity(150);
            rigidBody->setVel(transformation->getDirection()*transformation->getVelocity());
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Left))
        {
            aniGraphics->setAnimationType(Animationtype::RunLeft);
            transformation->setDirection(sf::Vector2f(-1, 0));
            transformation->setVelocity(150);
            rigidBody->setVel(transformation->getDirection() * transformation->getVelocity());
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Down))
        {
            aniGraphics->setAnimationType(Animationtype::RunDown);
            transformation->setDirection(sf::Vector2f(0, 1));
            transformation->setVelocity(150);
            rigidBody->setVel(transformation->getDirection() * transformation->getVelocity());
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Right))
        {
            aniGraphics->setAnimationType(Animationtype::RunRight);
            transformation->setDirection(sf::Vector2f(1, 0));
            transformation->setVelocity(150);
            rigidBody->setVel(transformation->getDirection() * transformation->getVelocity());
        }
    }
}

void MovementInputArrowsCP::init()
{

}