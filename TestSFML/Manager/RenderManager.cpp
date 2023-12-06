#include "stdafx.h"
#include "RenderManager.h"

void RenderManager::render()
{
	for (auto& comp : layersToRender)
	{
		comp->draw();
	}
}

void RenderManager::addToLayers(std::shared_ptr<RenderCP> renderCP)
{
	layersToRender.push_back(renderCP);
}
