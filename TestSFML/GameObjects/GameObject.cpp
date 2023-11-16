#include "GameObject.h"
#include <iostream>

void GameObject::addComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

void GameObject::update(float deltaTime) {
    for (auto& comp : components) {
        comp->update(deltaTime);
    }
}

void GameObject::init()
{
    for (auto& comp : components) {
        comp->init();
    }
}