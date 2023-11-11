#pragma once
#include "Components.h"
#include <iostream>

class  ColliderComponent : public Component
{ 
public:
	std::string Component::getId()
	{
		return component_id;
	}

	void Component::disableComonent()
	{
		m_Enabled = false;
	}

	void Component::enableComponent()
	{
		m_Enabled = true;
	}

	bool Component::enabled()
	{
		return m_Enabled;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self)
	{}

private:
	std::string component_id = "collider";
	bool m_Enabled = false;
};