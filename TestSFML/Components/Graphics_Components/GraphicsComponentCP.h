#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Component.h"

class GameObject;

class GraphicsComponent : public Component 
{
private:
    std::string componentId = "graphics";
    sf::Sprite sprite;

public:
    GraphicsComponent(std::weak_ptr<GameObject> gameObject, const sf::Sprite& sprite)
        : Component(gameObject), sprite(sprite) {}

    virtual ~GraphicsComponent() = default;

    std::string Component::getComponentId()
    {
        return componentId;
    }
};
