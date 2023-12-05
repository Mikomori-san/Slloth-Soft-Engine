#include "stdafx.h"
#include "MapLoader.h"
#include "../tileson.hpp"

using namespace sf;
using namespace std;

using GameObjectPtr = shared_ptr<GameObject>;
using TexturePtr = shared_ptr<sf::Texture>;
using SpritePtr = shared_ptr<sf::Sprite>;

void MapLoader::loadMap(const Vector2f& offset)
{
	tson::Tileson t;
	const std::unique_ptr<tson::Map> map = t.parse(m_resourcePath / "game.tmj");

	if (map->getStatus() == tson::ParseStatus::OK)
	{

		err() << "Load tile map with size: " << map->getSize().x << ", "
			<< map->getSize().y << " and tile size: " << map->getTileSize().x
			<< ", " << map->getTileSize().y << std::endl;

		for (auto& tileSet : map->getTilesets())
		{
			fs::path tileSetPath = tileSet.getImage().u8string();

			const auto texture = make_shared<sf::Texture>();
			if (!texture->loadFromFile((m_resourcePath / tileSetPath).string()))
			{
				err() << "Could not load texture " << m_resourcePath / tileSetPath << endl;
			}
			m_tileSetTexture[tileSet.getName()] = texture;
		}
	}
	else
	{
		std::cout << "Parse error: " << map->getStatusMessage() << std::endl;
	}

	// go through all layers
	m_layers.resize(map->getLayers().size());
	cout << m_layers.size() << endl;			// es gibt 5 layer
	for (int layerIdx = 0; layerIdx < static_cast<int>(map->getLayers().size()); layerIdx++)
	{
		auto layer = map->getLayers()[layerIdx];
		err() << "Load layer: " << layer.getName() << " with width: "
			<< layer.getSize().x << " and height: " << layer.getSize().y << std::endl;

		const int size = layer.getSize().x * layer.getSize().y;

		// iterate over all elements/tiles in the layer
		for (int i = 0; i < size; i++)
		{
			const auto gid = layer.getData()[i];

			if (gid == 0)
			{
				// 0 means there is no tile at this position.
				continue;
			}

			// get tile set for tile and allocate the corresponding tileSet texture
			const auto* const tileSet = map->getTilesetByGid(gid);
			const Vector2i tileSize(map->getTileSize().x, map->getTileSize().y);
			sf::Texture& texture = *m_tileSetTexture[tileSet->getName()];

			// calculate position of tile
			Vector2f position;
			position.x = i % layer.getSize().x * static_cast<float>(tileSize.x);
			position.y = i / layer.getSize().x * static_cast<float>(tileSize.y);
			position += offset;

			// number of tiles in tile set texture (horizontally)
			const int tileCountX = texture.getSize().x / tileSize.x;

			// calculate 2d idx of tile in tile set texture
			const int idx = gid - tileSet->getFirstgid();
			const int idxX = idx % tileCountX;
			const int idxY = idx / tileCountX;

			// calculate source area of tile in tile set texture
			IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

			// IMPORTANT: the tiles of the map are loaded here and put into layers as defined 
			// in the Tiled editor. The m_layers vector contains vectors of tile sprites, 
			// i.e., one vector of tile sprites for each layer. you can assign such a vector
			// to a TileLayerComponent, which is managed by the RenderManager. The RenderManager
			// takes care of rendering TileLayerComponents in the correct order 
			// (foreground, background, ...)			

			// create tile (Sprite) and put it into the appropriate layer.
			auto sprite = make_shared<sf::Sprite>();
			sprite->setTexture(texture);
			sprite->setTextureRect(source);
			sprite->setPosition(position.x, position.y);

			m_layers[layerIdx].push_back(sprite);
		}
	}


	for (auto group : map->getLayers())
	{
		// go over all objects per layer
		for (auto object : group.getObjects())
		{
			Vector2f position(object.getPosition().x, object.getPosition().y);
			position += offset;

			// example to get a texture rectangle for a sprite
			FloatRect bounds(position.x, position.y, object.getSize().x, object.getSize().y);
			// TODO: check out game.tmj and there the content contained within <object group name="Object Layer 1">
			// there you can see the properties that you can parse, that should help you set up the sprites
			cout << object.getRotation() << endl;
			cout << object.getType() << endl;
		}
	}
}

void MapLoader::drawLayer(sf::RenderWindow& m_window, const std::vector<SpritePtr>& layer)
{
	for (const auto& sprite : layer)
	{
		m_window.draw(*sprite);
	}
}
