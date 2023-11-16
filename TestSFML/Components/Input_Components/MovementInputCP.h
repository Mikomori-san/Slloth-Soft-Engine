#pragma once
#include "InputCP.h"
#include "../../Enums/Animationtype.h"
#include "../Graphics_Components/AnimatedGraphicsCP.h"
#include "../Transformation_Components/TransformationCP.h"

class MovementInputCP : protected InputCP
{
public:
	MovementInputCP(std::weak_ptr<GameObject> gameObject, std::string id, std::weak_ptr<AnimatedGraphicsCP> animatedGraphicsCP_, std::weak_ptr<TransformationCP> transformationCP_)
		: InputCP(gameObject, id), animatedGraphicsCP(animatedGraphicsCP_), transformationCP(transformationCP_)
	{}	
	~MovementInputCP() = default;
	
	std::string getComponentId() override { return this->componentId; }
	void setComponentId(std::string id) { this->componentId = id; }
	void update(float deltatime) override;
	void init() override;

private:
	std::weak_ptr<AnimatedGraphicsCP> animatedGraphicsCP;
	std::weak_ptr<TransformationCP> transformationCP;
	
	void processInput() override;
};
