#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include "../Components/Components.h"

class GameObject {
public:
    GameObject(int id);
    virtual ~GameObject();

    template <typename T, typename... Args>
    T* addComponent(Args&&... args);

    template <typename T>
    T* getComponent() const;

    void start();
    void update(float dt);
    void destroy();

    int getId() const;

private:
    int id;
    //std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

#include "GameObject.cpp" 