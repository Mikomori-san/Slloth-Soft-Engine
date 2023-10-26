#pragma once
#include "GameObject.h"
#include "../Animationtype.h"

class Player : public GameObject
{
public:
	Player();
	~Player() = default;
	
	sf::IntRect getCollisionRect() { return CollisionRect; }
	sf::IntRect getPlayerCollisionRect() { return PlayerCollisionRect; }
	
	void draw(sf::RenderWindow& window) override;
	void initialize() override;
	void update(float deltaTime) override;

	void setSprite(std::shared_ptr<sf::Texture> texture);

	sf::Sprite getAnimatedSprite() { return animatedSprite; }
	int* getAnimationTypeFramesCount() { return animationTypeFramesCount; }
	sf::Vector2i getColliderSize() { return colliderSize; }


private:
	sf::IntRect CollisionRect;
	sf::IntRect PlayerCollisionRect;
	sf::Sprite animatedSprite;
	sf::Vector2i colliderSize = sf::Vector2i{ 50, 60 };


	const float ANIMATION_SPEED = 8;
	const int TILING_X = 10;
	const int TILING_Y = 8;
	const float moveSpeed = 150.0;	
	
	int animationTypeFramesCount[8] = { 3, 3, 1, 3, 10, 10, 10, 10 };
	float animationTimeIndex;
	Animationtype m_animationType = Animationtype::IdleDown;
	
	void updateTransform();
	void updateCollider();
	void handleInput(float deltaTime);
	void handleIdle();
	void doAnimation();
};