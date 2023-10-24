#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:

	static AssetManager& instance() 
	{ 
		static AssetManager instance;
		return instance; 
	}

	std::map<std::string, sf::Texture> Textures = std::map<std::string, sf::Texture>{};
	std::map<std::string, sf::Sound> Sounds = std::map<std::string, sf::Sound>{};
	std::map<std::string, std::shared_ptr<sf::Music>> Music = std::map<std::string, std::shared_ptr<sf::Music>>{};
	std::map<std::string, sf::Font> Fonts = std::map<std::string, sf::Font>{};

	void loadTexture(const std::string& name, const std::string& fileName);
	void loadSound(const std::string& name, const std::string& fileName);
	void loadMusic(const std::string& name, const std::string& fileName);
	void loadFont(const std::string& name, const std::string& fileName);

private:

	AssetManager() = default;
	~AssetManager() = default;
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;
};