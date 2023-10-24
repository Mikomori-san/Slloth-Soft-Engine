#include "AssetManager.h"
#include <iostream>

void AssetManager::loadTexture(const std::string& name, const std::string& fileName)
{
	sf::Texture texture;
	
	if (!texture.loadFromFile(fileName))
	{
		std::cout << "The file has not been found..." << std::endl;
		return;
	}

	Textures[name] = texture;
}

void AssetManager::loadSound(const std::string& name, const std::string& fileName)
{
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(fileName))
	{
		std::cout << "The file has not been found..." << std::endl;
		return;
	}

	sf::Sound sound;
	sound.setBuffer(buffer);

	Sounds[name] = sound;
}

void AssetManager::loadMusic(const std::string& name, const std::string& fileName)
{
	std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();

	if (!music->openFromFile(fileName))
	{
		std::cout << "The file has not been found..." << std::endl;
	}
	
	Music[name] = music;

}

void AssetManager::loadFont(const std::string& name, const std::string& fileName)
{
	sf::Font font;

	if (!font.loadFromFile(fileName))
	{
		std::cout << "The file has not been found..." << std::endl;
		return;
	}

	Fonts[name] = font;
}