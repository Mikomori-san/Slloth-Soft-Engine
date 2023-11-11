#include "GameObject.h"
#include <iostream>

void GameObject::addComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
}

void GameObject::update() {
    for (auto& comp : components) {
        comp->update();
    }
}