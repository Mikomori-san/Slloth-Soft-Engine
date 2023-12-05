#include "stdafx.h"
#include "MenuState.h"
#include "../GameObject.h"
#include "../Components/Graphics_Components/LayerCP.h"
#include "../tileson.hpp"

void MenuState::init(sf::RenderWindow& rWindow)
{
	this->window.reset(&rWindow, [](sf::RenderWindow*) {});

	loadMap("game.tmj", sf::Vector2f());		// TODO: Implement a RenderManager class that renders sprites/tile layers in the correct order
								// TODO: Add objects to an object layer of the tile map in the Tiled Map Editor and load them into the game

	map = std::make_shared<GameObject>("Map");
	int layerCount = 0;

	for (auto& layer : m_layers)
	{
		map->addComponent(std::make_shared<LayerCP>(map, "Layer" + layerCount + 1, window, layerCount, m_layers[layerCount]));
		layerCount++;
	}
	
	gameObjects.push_back(map);

	for (auto& go : gameObjects)
	{
		go->init();
	}
}

void MenuState::exit()
{
	for (auto& go : gameObjects)
	{
		go.reset();
	}
	gameObjects.clear();

}

void MenuState::update(float deltaTime)
{
	
}

void MenuState::render()
{
	for (auto& go : gameObjects) {
		for (auto& render : go->getComponentsOfType<RenderCP>())
		{
			render->draw();
		}
	}
}

void MenuState::loadMap(std::string name, const sf::Vector2f& offset)
{
	tson::Tileson t;
	const std::unique_ptr<tson::Map> map = t.parse(m_resourcePath / name);

	if (map->getStatus() == tson::ParseStatus::OK)
	{

		sf::err() << "Load tile map with size: " << map->getSize().x << ", "
			<< map->getSize().y << " and tile size: " << map->getTileSize().x
			<< ", " << map->getTileSize().y << std::endl;

		for (auto& tileSet : map->getTilesets())
		{
			fs::path tileSetPath = tileSet.getImage().u8string();

			const auto texture = std::make_shared<sf::Texture>();
			if (!texture->loadFromFile((m_resourcePath / tileSetPath).string()))
			{
				sf::err() << "Could not load texture " << m_resourcePath / tileSetPath << std::endl;
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
	std::cout << m_layers.size() << std::endl;			// es gibt 5 layer
	for (int layerIdx = 0; layerIdx < static_cast<int>(map->getLayers().size()); layerIdx++)
	{
		auto layer = map->getLayers()[layerIdx];
		sf::err() << "Load layer: " << layer.getName() << " with width: "
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
			const sf::Vector2i tileSize(map->getTileSize().x, map->getTileSize().y);
			sf::Texture& texture = *m_tileSetTexture[tileSet->getName()];

			// calculate position of tile
			sf::Vector2f position;
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
			sf::IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

			// IMPORTANT: the tiles of the map are loaded here and put into layers as defined 
			// in the Tiled editor. The m_layers vector contains vectors of tile sprites, 
			// i.e., one vector of tile sprites for each layer. you can assign such a vector
			// to a TileLayerComponent, which is managed by the RenderManager. The RenderManager
			// takes care of rendering TileLayerComponents in the correct order 
			// (foreground, background, ...)			

			// create tile (Sprite) and put it into the appropriate layer.
			auto sprite = std::make_shared<sf::Sprite>();
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
			sf::Vector2f position(object.getPosition().x, object.getPosition().y);
			position += offset;

			// example to get a texture rectangle for a sprite
			sf::FloatRect bounds(position.x, position.y, object.getSize().x, object.getSize().y);
			// TODO: check out game.tmj and there the content contained within <object group name="Object Layer 1">
			// there you can see the properties that you can parse, that should help you set up the sprites
			std::cout << object.getRotation() << std::endl;
			std::cout << object.getType() << std::endl;
		}
	}
}
