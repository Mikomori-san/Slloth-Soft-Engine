#pragma once
#include "InputCP.h"
#include "../../Enums/Animationtype.h"
#include "../Graphics_Components/AnimatedGraphicsCP.h"

class MovementInputCP : InputCP
{
public:
	MovementInputCP(std::weak_ptr<GameObject> gameObject, std::string id, std::weak_ptr<AnimatedGraphicsCP> animatedGraphicsCP_)
		: InputCP(gameObject, id), animatedGraphicsCP(animatedGraphicsCP_)
	{}	
	~MovementInputCP() = default;
	
	std::string getComponentId() override { return componentId; }
	void update(float deltatime) override;

private:
	std::weak_ptr<AnimatedGraphicsCP> animatedGraphicsCP;
};
