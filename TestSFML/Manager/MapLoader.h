#pragma once
#include "../GameObjects/GameObject.h"
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

using namespace sf;
using namespace std;

using TexturePtr = shared_ptr<Texture>;
using SpritePtr = shared_ptr<Sprite>;
using GameObjectPtr = shared_ptr<GameObject>;


class MapLoader
{
public:

	static MapLoader& getInstance()
	{
		static MapLoader instance;
		return instance;
	}

private:
	void loadMap(const fs::path& filename, const Vector2f& offset);

	unordered_map<string, TexturePtr> m_tileSetTexture;
	const fs::path m_resourcePath{ "../Assets/Maps/" };

	vector<vector<SpritePtr>> m_layers;
	unordered_map<string, GameObjectPtr> m_objects;
};