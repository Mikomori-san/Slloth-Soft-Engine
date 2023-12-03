#include "stdafx.h"
#include "MovementInputArrowsCP.h"
#include <iostream>

void MovementInputArrowsCP::update(float deltatime)
{
    processInput();
}

void MovementInputArrowsCP::processInput()
{
    if (!animatedGraphicsCP.expired() && !transformationCP.expired() && !gameObject.expired())
    {
        std::shared_ptr<GameObject> go = gameObject.lock();
        std::shared_ptr<AnimatedGraphicsCP> aniGraphics = animatedGraphicsCP.lock();
        std::shared_ptr<TransformationCP> transformation = transformationCP.lock();

        transformation->setVelocity(0);

        if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Up))
        {
            aniGraphics->setAnimationType(Animationtype::RunUp);
            transformation->setDirection(sf::Vector2f(0, -1));
            transformation->setVelocity(150);
            std::cout << go->getId() << " PosX: " << transformation->getPosition().x << std::endl;
            std::cout << go->getId() << " PosY: " << transformation->getPosition().y << std::endl;
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Left))
        {
            aniGraphics->setAnimationType(Animationtype::RunLeft);
            transformation->setDirection(sf::Vector2f(-1, 0));
            transformation->setVelocity(150);
            std::cout << go->getId() << " PosX: " << transformation->getPosition().x << std::endl;
            std::cout << go->getId() << " PosY: " << transformation->getPosition().y << std::endl;
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Down))
        {
            aniGraphics->setAnimationType(Animationtype::RunDown);
            transformation->setDirection(sf::Vector2f(0, 1));
            transformation->setVelocity(150);
            std::cout << go->getId() << " PosX: " << transformation->getPosition().x << std::endl;
            std::cout << go->getId() << " PosY: " << transformation->getPosition().y << std::endl;
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Right))
        {
            aniGraphics->setAnimationType(Animationtype::RunRight);
            transformation->setDirection(sf::Vector2f(1, 0));
            transformation->setVelocity(150);
            std::cout << go->getId() << " PosX: " << transformation->getPosition().x << std::endl;
            std::cout << go->getId() << " PosY: " << transformation->getPosition().y << std::endl;
        }
    }
}

void MovementInputArrowsCP::init()
{

}