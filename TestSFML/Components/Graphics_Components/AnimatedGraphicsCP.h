#pragma once
#include "GraphicsCP.h"

class AnimatedGraphicsCP : public GraphicsCP {
private:
    int rows;
    int columns;
    std::string specificComponentId = "animatedGC";

public:
    AnimatedGraphicsCP(std::weak_ptr<GameObject> gameObject, const sf::Sprite& sprite, int rows, int columns) 
        : GraphicsCP(gameObject, sprite), rows(rows), columns(columns) {}
    
    void update() override;

    std::string Component::getSpecificComponentId()
    {
        return specificComponentId;
    }
};