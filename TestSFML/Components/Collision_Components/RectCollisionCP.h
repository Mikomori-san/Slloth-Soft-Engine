#pragma once
#include "../Component.h"
class RectCollisionCP : public Component
{
public:

    RectCollisionCP(std::weak_ptr<GameObject> gameObject, std::string id) : Component(gameObject, id){}

    void update(float deltaTime) override;
    std::string getComponentId() override { return this->componentId; };
    void setComponentId(std::string id) override { this->componentId = id; }
    void init() override;
    sf::IntRect& getCollisionRect() { return collisionRect; }
    void setCollisionRect(sf::IntRect& colRect) { this->collisionRect = colRect; }
private:
    sf::IntRect collisionRect;
    sf::Vector2i colliderSize = sf::Vector2i{ 50, 60 };
    sf::IntRect PlayerCollisionRect;

    void updateCollider(std::shared_ptr<GameObject> go);
};