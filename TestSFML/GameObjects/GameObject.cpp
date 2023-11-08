#include "GameObject.h"

GameObject::GameObject(int id) : id(id) {}

GameObject::~GameObject() {
    destroy();
}

void GameObject::start() {
    /*for (auto& [type, comp] : components) {
        comp->start();
    }*/
}

void GameObject::update(float dt) {
    /*for (auto& [type, comp] : components) {
        comp->update(dt);
    }*/
}

void GameObject::destroy() {
    //components.clear();
}

int GameObject::getId() const {
    return id;
}