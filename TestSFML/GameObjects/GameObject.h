#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../Components/Component.h"

class Component;

class GameObject
{
public:
	GameObject(std::string id) : id(id){}

	~GameObject(){}

	void addComponent(std::shared_ptr<Component> component);
	void update(float deltaTime);
    void init();
	std::vector<std::shared_ptr<Component>>& getComponents() { return components; }
	std::shared_ptr<Component> getComponent(std::string id);
	std::string getId() { return  this->id; }
	void setId(std::string id) { this->id = id; }

private:

	std::string id;
	std::vector<std::shared_ptr<Component>> components;
};