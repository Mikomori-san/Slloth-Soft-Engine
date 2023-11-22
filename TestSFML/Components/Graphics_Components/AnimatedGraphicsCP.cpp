#include "stdafx.h"
#include "AnimatedGraphicsCP.h"
#include "../../DebugDraw.h"
#include "../Transformation_Components/TransformationCP.h"
#include "../Collision_Components/RectCollisionCP.h"

void AnimatedGraphicsCP::init()
{
	sprite->setScale(sf::Vector2f(1, 1));
	sprite->setPosition(sf::Vector2f(0, 0));

	sprite->setTextureRect(sf::IntRect(
		0,
		0,
		sprite->getTextureRect().width / TILING_X,
		sprite->getTextureRect().height / TILING_Y
	));
}

void AnimatedGraphicsCP::update(float deltaTime)
{
	animationTimeIndex += deltaTime * ANIMATION_SPEED;
	handleIdle();
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();
		std::shared_ptr<TransformationCP> transform = std::dynamic_pointer_cast<TransformationCP>(go->getComponent("PlayerTransformationCP"));

		sprite->setPosition(transform->getPosition());
		sprite->setRotation(transform->getRotation());
		sprite->setScale(transform->getScale(), transform->getScale());
		sprite->setOrigin(transform->getOrigin());
	}
}

void AnimatedGraphicsCP::draw()
{
	doAnimation();
	window->draw(*sprite);

	DebugDraw::getInstance().drawRectOutline(
		sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top),
		static_cast<int>(sprite->getGlobalBounds().width),
		static_cast<int>(sprite->getGlobalBounds().height),
		sf::Color::Red
	);
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();
		std::shared_ptr<RectCollisionCP> collision = std::dynamic_pointer_cast<RectCollisionCP>(go->getComponent("PlayerCollisionCP"));
		DebugDraw::getInstance().drawRectOutline(collision->getCollisionRect(), sf::Color::Green);
	}
}

void AnimatedGraphicsCP::setSprite(std::shared_ptr<sf::Texture> texture)
{
	this->sprite->setTexture(*texture);
}

void AnimatedGraphicsCP::setAnimationType(Animationtype type)
{
	this->m_animationType = type;
}

void AnimatedGraphicsCP::doAnimation()
{
	auto animationFrame = (int)animationTimeIndex % animationTypeFramesCount[(int)m_animationType];

	sf::IntRect textureRect;
	textureRect.left = animationFrame * sprite->getTextureRect().width;
	textureRect.top = m_animationType * sprite->getTextureRect().height;
	textureRect.width = sprite->getTextureRect().width;
	textureRect.height = sprite->getTextureRect().height;

	sprite->setTextureRect(textureRect);
}

void AnimatedGraphicsCP::handleIdle()
{
	switch (m_animationType)
	{
	case RunDown:
		m_animationType = Animationtype::IdleDown;
		break;
	case RunLeft:
		m_animationType = Animationtype::IdleLeft;
		break;
	case RunUp:
		m_animationType = Animationtype::IdleUp;
		break;
	case RunRight:
		m_animationType = Animationtype::IdleRight;
		break;
	default:
		break;
	}
}
