#include "stdafx.h"
#include "MovementInput_WASD_CP.h"
#include <iostream>

void MovementInputWASDCP::update(float deltatime)
{
    processInput();
}

void MovementInputWASDCP::processInput()
{
    if (!animatedGraphicsCP.expired() && !transformationCP.expired() && !gameObject.expired())
    {
        std::shared_ptr<GameObject> go = gameObject.lock();
        std::shared_ptr<AnimatedGraphicsCP> aniGraphics = animatedGraphicsCP.lock();
        std::shared_ptr<TransformationCP> transformation = transformationCP.lock();

        transformation->setVelocity(0);

        if (InputManager::getInstance().getKeyPressed(sf::Keyboard::W))
        {
            aniGraphics->setAnimationType(Animationtype::RunUp);
            transformation->setDirection(sf::Vector2f(0, -1));
            transformation->setVelocity(150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::A))
        {
            aniGraphics->setAnimationType(Animationtype::RunLeft);
            transformation->setDirection(sf::Vector2f(-1, 0));
            transformation->setVelocity(150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::S))
        {
            aniGraphics->setAnimationType(Animationtype::RunDown);
            transformation->setDirection(sf::Vector2f(0, 1));
            transformation->setVelocity(150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::D))
        {
            aniGraphics->setAnimationType(Animationtype::RunRight);
            transformation->setDirection(sf::Vector2f(1, 0));
            transformation->setVelocity(150);
        }
    }
}

void MovementInputWASDCP::init()
{

}
