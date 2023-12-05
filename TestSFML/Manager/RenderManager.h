#pragma once

class RenderManager
{
public:
	static RenderManager& getInstance()
	{
		static RenderManager instance;
		return instance;
	}


};