#include "stdafx.h"
#include "MovementInputWASDCP.h"
#include <iostream>
#include "../DecisionHandlerCP.h"

void MovementInputWASDCP::update(float deltatime)
{
    processInput();
}

void MovementInputWASDCP::processInput()
{
    if (!gameObject.expired())
    {
        gameObject.lock()->getComponentsOfType<TransformationCP>().at(0)->setVelocity(0);

        std::shared_ptr<DecisionHandlerCP> decHandler = gameObject.lock()->getComponentsOfType<DecisionHandlerCP>().at(0);

        if (InputManager::getInstance().getKeyPressed(sf::Keyboard::W))
        {
            decHandler->handleMovement(Direction::up, sf::Vector2f(0, -1), 150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::A))
        {
            decHandler->handleMovement(Direction::left, sf::Vector2f(-1, 0), 150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::S))
        {
            decHandler->handleMovement(Direction::down, sf::Vector2f(0, 1), 150);
        }
        else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::D))
        {
            decHandler->handleMovement(Direction::right, sf::Vector2f(1, 0), 150);
        }
    }
}

void MovementInputWASDCP::init()
{

}
