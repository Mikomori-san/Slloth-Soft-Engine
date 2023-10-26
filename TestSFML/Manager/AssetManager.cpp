#include "AssetManager.h"
#include <iostream>

std::map<std::string, std::shared_ptr<sf::Texture>> AssetManager::Textures = std::map<std::string, std::shared_ptr<sf::Texture>>{};
std::map<std::string, std::shared_ptr<sf::Sound>> AssetManager::Sounds = std::map<std::string, std::shared_ptr<sf::Sound>>{};
std::map<std::string, std::shared_ptr<sf::Music>> AssetManager::Music = std::map<std::string, std::shared_ptr<sf::Music>>{};
std::map<std::string, std::shared_ptr<sf::Font>> AssetManager::Fonts = std::map<std::string, std::shared_ptr<sf::Font>>{};

void AssetManager::loadTexture(const std::string& name, const std::string& fileName)
{
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
	
	if (!texture->loadFromFile(fileName))
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

	std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();
	sound->setBuffer(buffer);

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
	std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();

	if (!font->loadFromFile(fileName))
	{
		std::cout << "The file has not been found..." << std::endl;
		return;
	}

	Fonts[name] = font;
}