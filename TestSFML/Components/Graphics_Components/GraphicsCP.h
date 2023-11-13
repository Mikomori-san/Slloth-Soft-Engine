#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Component.h"

class GameObject;

class GraphicsCP : public Component 
{
private:
    std::string componentId = "graphics";
    sf::Sprite sprite;

public:
    GraphicsCP(std::weak_ptr<GameObject> gameObject, const sf::Sprite& sprite)
        : Component(gameObject), sprite(sprite) {}

    virtual ~GraphicsCP() = default;

    std::string Component::getComponentId()
    {
        return componentId;
    }
};
