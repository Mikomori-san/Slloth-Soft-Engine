#include "stdafx.h"
#include "RectCollisionCP.h"
#include "../Graphics_Components/AnimatedGraphicsCP.h"
#include "../Transformation_Components/TransformationCP.h"

void RectCollisionCP::update(float deltaTime)
{
    if (!gameObject.expired())
    {
        std::shared_ptr<GameObject> go = gameObject.lock();
        updateCollider(go);

        std::shared_ptr<AnimatedGraphicsCP> ani = std::dynamic_pointer_cast<AnimatedGraphicsCP>(go->getComponent("PlayerSpriteCP"));
        std::shared_ptr<TransformationCP> transf = std::dynamic_pointer_cast<TransformationCP>(go->getComponent("PlayerTransformationCP"));
        PlayerCollisionRect = sf::IntRect(
            (int)transf->getPosition().x,
            (int)transf->getPosition().y,
            (int)ani->getSprite().getGlobalBounds().width,
            (int)ani->getSprite().getGlobalBounds().height
        );
    }
}

void RectCollisionCP::init()
{
    if (!gameObject.expired())
    {
        std::shared_ptr<GameObject> go = gameObject.lock();
        updateCollider(go);
    }
}

void RectCollisionCP::updateCollider(std::shared_ptr<GameObject> go)
{
    std::shared_ptr<TransformationCP> playerCol = std::dynamic_pointer_cast<TransformationCP>(go->getComponent("PlayerTransformationCP"));
        collisionRect = sf::IntRect(
            (int)playerCol->getPosition().x - colliderSize.x / 2,
            (int)playerCol->getPosition().y - colliderSize.y / 2,
            colliderSize.x,
            colliderSize.y);
}