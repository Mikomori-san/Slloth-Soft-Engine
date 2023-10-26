#include "Player.h"
#include "../Manager/InputManager.h"
#include "../DebugDraw.h"


Player::Player() : animationTimeIndex(0){}

void Player::draw(sf::RenderWindow& window)
{
    doAnimation();

    window.draw(animatedSprite);

    DebugDraw::getInstance().drawRectOutline(
        sf::Vector2f(animatedSprite.getGlobalBounds().left, animatedSprite.getGlobalBounds().top),
        static_cast<int>(animatedSprite.getGlobalBounds().width),
        static_cast<int>(animatedSprite.getGlobalBounds().height),
        sf::Color::Red
    );

    DebugDraw::getInstance().drawRectOutline(CollisionRect, sf::Color::Green);
}

void Player::initialize()
{
    animatedSprite.setScale(sf::Vector2f(1, 1));
    animatedSprite.setPosition(sf::Vector2f(0, 0));

    animatedSprite.setTextureRect(sf::IntRect(
        0,
        0,
        animatedSprite.getTextureRect().width / TILING_X,
        animatedSprite.getTextureRect().height / TILING_Y
    ));

    setOrigin(sf::Vector2f(animatedSprite.getTextureRect().width / 2, animatedSprite.getTextureRect().height / 2));

    updateTransform();
    updateCollider();
}

void Player::update(float deltaTime)
{
    updateTransform();
    updateCollider();
    handleIdle();

    handleInput(deltaTime);

    animationTimeIndex += deltaTime * ANIMATION_SPEED;

    PlayerCollisionRect = sf::IntRect(
        (int)getPosition().x,
        (int)getPosition().y,
        (int)animatedSprite.getGlobalBounds().width,
        (int)animatedSprite.getGlobalBounds().height
    );
}

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

void Player::handleIdle()
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

void Player::doAnimation()
{
	auto animationFrame = (int)animationTimeIndex % animationTypeFramesCount[(int)m_animationType];

    sf::IntRect textureRect;
    textureRect.left = animationFrame * animatedSprite.getTextureRect().width;
    textureRect.top = m_animationType * animatedSprite.getTextureRect().height;
    textureRect.width = animatedSprite.getTextureRect().width;
    textureRect.height = animatedSprite.getTextureRect().height;

    animatedSprite.setTextureRect(textureRect);

}