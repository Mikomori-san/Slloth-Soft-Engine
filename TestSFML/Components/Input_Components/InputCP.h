#pragma once
#include "../Component.h"
#include "../../Manager/InputManager.h"


class InputCP : Component
{
public:
	InputCP(std::weak_ptr<GameObject> gameObject, std::string id)
		: Component(gameObject, id) 
	{}

	virtual ~InputCP() = default;

	virtual std::string getComponentId() override { return componentId; }
	virtual void update(float deltaTime) override;
	virtual void procesInput();

private:

};