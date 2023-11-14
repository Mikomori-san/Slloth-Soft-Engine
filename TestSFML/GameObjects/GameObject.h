#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../Components/Component.h"

class GameObject
{
public:
	GameObject(sf::Vector2f initPosition, std::string id) : position(initPosition), id(id){}

	~GameObject(){}

	void addComponent(std::shared_ptr<Component> component);
	void update(float deltaTime);
	void setVelocity(float newVelocity);
	void setPosition(sf::Vector2f newPosition);
	void setDirectin(sf::Vector2f newDirection);
    void init();
private:
	float velocity;

	sf::Vector2f position;
	sf::Vector2f direction;

	std::string id;
	
	std::vector<std::shared_ptr<Component>> components;
};


/*

Player Initialize:

	setOrigin(sf::Vector2f(animatedSprite.getTextureRect().width / 2, animatedSprite.getTextureRect().height / 2));

	updateTransform();
	updateCollider();

Player Update:

updateTransform();
updateCollider();

handleInput(deltaTime);

PlayerCollisionRect = sf::IntRect(
	(int)getPosition().x,
	(int)getPosition().y,
	(int)animatedSprite.getGlobalBounds().width,
	(int)animatedSprite.getGlobalBounds().height
);


void Player::updateTransform()
{
    animatedSprite.setPosition(getPosition());
    animatedSprite.setRotation(getRotation());
    animatedSprite.setScale(getScale());
    animatedSprite.setOrigin(getOrigin());
}

void Player::updateCollider()
{
    CollisionRect = sf::IntRect(
        (int)getPosition().x - colliderSize.x / 2,
        (int)getPosition().y - colliderSize.y / 2,
        colliderSize.x,
        colliderSize.y);
}

void Player::handleInput(float deltaTime)
{
    if (InputManager::getInstance().getKeyPressed(sf::Keyboard::W))
    {
        m_animationType = Animationtype::RunUp;
        move(sf::Vector2f(0, -1) * moveSpeed * deltaTime);
    }
    else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::A))
    {
        m_animationType = Animationtype::RunLeft;
        move(sf::Vector2f(-1, 0) * moveSpeed * deltaTime);
    }
    else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::S))
    {
        m_animationType = Animationtype::RunDown;
        move(sf::Vector2f(0, 1) * moveSpeed * deltaTime);
    }
    else if (InputManager::getInstance().getKeyPressed(sf::Keyboard::D))
    {
        m_animationType = Animationtype::RunRight;
        move(sf::Vector2f(1, 0) * moveSpeed * deltaTime);
    }
}
*/