#pragma once
#include "../Component.h"

class RigidBodyCP : public Component
{
public:
    RigidBodyCP(std::weak_ptr<GameObject> go, std::string id, const float newMass, const float newInvMass) : Component(go, id), mass(newMass), invMass(newInvMass) {};
    ~RigidBodyCP() = default;

    void init() override {};
    void update(float deltaTime) override {};

    std::string getComponentId() override { return this->componentId; }
    void setComponentId(std::string componentId) override { this->componentId = componentId; }
private:
    float mass;
    float invMass;

    std::vector<sf::Vector2f> forces;
    std::vector<sf::Vector2f> impulses;

    sf::Vector2f acceleration;
    sf::Vector2f velocity;
};