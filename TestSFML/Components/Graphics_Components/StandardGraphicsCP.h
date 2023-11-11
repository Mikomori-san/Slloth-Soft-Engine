#pragma once
#include "GraphicsComponent.h"

class StandardGraphicsCP : public GraphicsComponent
{
private:
    std::string specificComponentId = "standardGC";
public:
    StandardGraphicsCP(std::weak_ptr<GameObject> gameObject, const sf::Sprite& sprite)
        : GraphicsComponent(gameObject, sprite) {}

    void update() override;

    void receive(int message) override;

    std::string Component::getSpecificComponentId()
    {
        return specificComponentId;
    }
};
