#pragma once
#include <vector>
#include "../Components/Render_Components/RenderCP.h"

class RenderManager
{
public:
	static RenderManager& getInstance()
	{
		static RenderManager instance;
		return instance;
	}

	void render();
	void addToLayers(std::shared_ptr<RenderCP> renderCP);

private:
	std::vector<std::shared_ptr<RenderCP>> layersToRender;
};