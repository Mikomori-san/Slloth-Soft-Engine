#include "stdafx.h"
#include "MapLoader.h"
#include "../tileson.hpp"

void MapLoader::loadMap(const fs::path& filename, const Vector2f& offset)
{
	tson::Tileson t;
	const std::unique_ptr<tson::Map> map = t.parse(filename);

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		err() << "Load tile map with size: " << map->getSize().x << ", "
			<< map->getSize().y << " and tile size: " << map->getTileSize().x
			<< ", " << map->getTileSize().y << std::endl;

		for (auto& tileSet : map->getTilesets())
		{
			fs::path tileSetPath = tileSet.getImage().u8string();

			const auto texture = make_shared<Texture>();
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
			Texture& texture = *m_tileSetTexture[tileSet->getName()];

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
			auto sprite = make_shared<Sprite>();
			sprite->setTexture(texture);
			sprite->setTextureRect(source);
			sprite->setPosition(position.x, position.y);

			m_layers[layerIdx].push_back(sprite);
		}
	}

	//// IMPORTANT: this is the second important loop. Here the game objects defined in the 
	//// Tiled editor are loaded (object layer). These game objects can easily be converted
	//// to your GameObjects used in-game. Helper functions help you structure your code, e.g.,
	//// createEnemy, createPlayer, createTreasureChest, ...
	//// These helper functions parse the information and create the correct GameObjects and Components
	//// for the GameObjects. 
	//// Ideally the GameStates do not contain any object generation code anymore. Objects are loaded
	//// from the Tiled editor file, i.e., have been placed in the Tiled editor.

	//// go through all object layers
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

			// TODO check data of object (position, type, etc.) 
			// type can be used to check for type of component that needs to be created.
			// In the exercise it is a GameObject by itself, in the assignments/engine 
			// think about configuring components for a GameObject.

			// TODO use data to initialize a sprite (texture rect, position, texture name, game object id...)

			/*
			if (object.getType() == "Sprite")
			{
				// IMPORTANT: a very simple sprite GameObject is created here. for your
				// assignment use the component-based architecture (e.g., GameObject + SpriteRenderComponent)
				const auto sprite = loadSprite(object);
				m_objects[object.getName()] = sprite;
			}
			*/
		}
	}
}

GameObjectPtr MapLoader::loadSprite(tson::Object& object) const
{
	auto gameObject = make_shared<GameObject>();

	IntRect textureRect{};
	textureRect.width = object.getSize().x;
	textureRect.height = object.getSize().y;

	// IMPORTANT: note how custom attributes (object->properties) created 
	// in the Tiled editor are parsed and used to initialize data for Components and
	// GameObjects.	
	// also note again: the GameObject is simplified for this example. A SpriteComponent should
	// be created instead.
	for (const auto* const property : object.getProperties().get())
	{
		auto name = property->getName();
		if (name == "Texture" &&
			!gameObject->m_texture.loadFromFile((m_resourcePath / std::any_cast<string>(property->getValue())).string()))
		{
			err() << "loadSprite: Could not load texture for sprite: " <<
				m_resourcePath / std::any_cast<string>(property->getValue()) << endl;
		}
		else if (name == "TextureRectLeft")
		{
			textureRect.left = std::any_cast<int>(property->getValue());
		}
		else if (name == "TextureRectTop")
		{
			textureRect.top = std::any_cast<int>(property->getValue());
		}
	}
	gameObject->m_sprite.setTexture(gameObject->m_texture);
	gameObject->m_sprite.setTextureRect(textureRect);
	gameObject->m_sprite.setPosition(object.getPosition().x, object.getPosition().y);
	return gameObject;
}


/*
bool init()
	{
		const VideoMode vm(800, 600);
		m_window.create(vm, "GameDev1 - TileMap Demo");
		m_window.setFramerateLimit(60);

		if (!m_offscreen.create(vm.width, vm.height))
		{
			err() << "Could not initialize offscreen render target" << endl;
			return false;
		}
		// We use the offscreen texture to avoid interpolation
		// artifacts. For this purpose, we have to activate smoothing.
		m_offscreen.setSmooth(true);
		m_offscreenSprite.setTexture(m_offscreen.getTexture());

		loadMap(m_resourcePath / "game.tmj", Vector2f());

		return true;
	}

	void update()
	{
		static Clock clock; ///< starts the clock
		const Time deltaTime = clock.restart();
		const float fDeltaTimeSeconds = deltaTime.asSeconds();

		constexpr float fScrollBaseSpeed = 10.0F; ///< pixels / second

		// Hint: move pixel precise to avoid camera artifacts, but
		// accumulate changes over time. Otherwise, the camera may
		// not move at all.
		m_fScrollOffset += fDeltaTimeSeconds * fScrollBaseSpeed;
		m_fScrollOffsetPixelPrecise = floor(m_fScrollOffset);
		m_fScrollOffset -= m_fScrollOffsetPixelPrecise;
	}

	static void drawLayer(RenderTarget& renderTarget, const vector<SpritePtr>& layer)
	{
		for (const auto& sprite : layer)
		{
			renderTarget.draw(*sprite);
		}
	}

	void draw()
	{
		m_window.clear();

		// move camera pixel precisely to avoid render artifacts
		View view = m_window.getView();
		view.move(m_fScrollOffsetPixelPrecise, 0.0F);
		m_window.setView(view);

		// draw layers
		// IMPORTANT: you can provides IDs for layers so that a
		// RenderManager can render layers in the correct order. The order
		// can be specified as custom attribute in Tiled. then you
		// do not have to hard code the render order as done here.
		drawLayer(m_window, m_layers[0]); // Floor
		drawLayer(m_window, m_layers[1]); // Background
		for (auto& object : m_objects)
		{
			m_window.draw(object.second->m_sprite);
		}
		drawLayer(m_window, m_layers[2]); // Player/Objects
		drawLayer(m_window, m_layers[3]); // Top

		m_window.display();
	}
*/