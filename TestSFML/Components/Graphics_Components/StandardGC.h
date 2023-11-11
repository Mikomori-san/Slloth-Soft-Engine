#pragma once
#include "GraphicsComponent.h"

class StandardGC : public GraphicsComponent 
{
private:
    std::string specificComponentId = "standardGC";
public:
    StandardGC(std::weak_ptr<GameObject> gameObject, const sf::Sprite& sprite)
        : GraphicsComponent(gameObject, sprite) {}

    void update() override;

    void receive(int message) override;

    std::string Component::getSpecificComponentId()
    {
        return specificComponentId;
    }
};
