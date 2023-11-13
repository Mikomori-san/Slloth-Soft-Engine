#pragma once
#include "GraphicsComponentCP.h"

class StandardGraphicsCP : public GraphicsComponent
{
private:
    std::string specificComponentId = "standardGC";
public:
    StandardGraphicsCP(std::weak_ptr<GameObject> gameObject, const sf::Sprite& sprite)
        : GraphicsComponent(gameObject, sprite) {}

    void update() override;

    std::string Component::getSpecificComponentId()
    {
        return specificComponentId;
    }
};
