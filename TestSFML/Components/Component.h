#pragma once
#include "../GameObjects/GameObject.h"
#include <string>

class Component
{
private:
    std::weak_ptr<GameObject> gameObject;

public:
    Component(std::weak_ptr<GameObject> gameObject)
        : gameObject(gameObject) {}

    virtual ~Component() = default;
    virtual void update() = 0;
    virtual std::string getComponentId() = 0;
    virtual std::string getSpecificComponentId() = 0;
};