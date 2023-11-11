#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../Components/Components.h"

class GameObject
{
public:
	int velocity;
	int x, y;
	void addComponent(std::shared_ptr<Component> component);
	void update();
	void sendMessage(int message);

private:
	std::vector<std::shared_ptr<Component>> components;
};


