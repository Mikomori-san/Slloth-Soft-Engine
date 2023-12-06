#pragma once
#include <memory>
#include "../Component.h"

class PoolObjectCP : public Component
{
public:
	PoolObjectCP(std::weak_ptr<GameObject> gameObject, std::string id)
		: Component(gameObject, id)
	{}

	~PoolObjectCP() = default;

	void SetActive(bool IsActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int Index);

	bool IsActive();
	int GetPoolIndex();

private:

	bool active;
	float lifeSpan = 0.0f;
	int PoolIndex;
};
