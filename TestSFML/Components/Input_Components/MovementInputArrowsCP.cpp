#include "stdafx.h"
#include "MovementInputArrowsCP.h"
#include <iostream>
#include "../DecisionHandlerCP.h"

void MovementInputArrowsCP::update(float deltatime)
{
    processInput();
}

void MovementInputArrowsCP::processInput()
{
    if (!gameObject.expired())
    {
        gameObject.lock()->getComponentsOfType<TransformationCP>().at(0)->setVelocity(0);

        std::shared_ptr<DecisionHandlerCP> decHandler = gameObject.lock()->getComponentsOfType<DecisionHandlerCP>().at(0);

        if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Up))
        {
            decHandler->handleMovement(Direction::up, sf::Vector2f(0, -1), 150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Left))
        {
            decHandler->handleMovement(Direction::left, sf::Vector2f(-1, 0), 150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Down))
        {
            decHandler->handleMovement(Direction::down, sf::Vector2f(0, 1), 150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::Right))
        {
            decHandler->handleMovement(Direction::right, sf::Vector2f(1, 0), 150);
        }
    }
}

void MovementInputArrowsCP::init()
{

}