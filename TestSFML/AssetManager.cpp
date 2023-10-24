#include "AssetManager.h"
#include <iostream>

void AssetManager::loadTexture(char* name, char* fileName)
{
	sf::Texture texture;
	
	if (!texture.loadFromFile(fileName))
	{
		std::cout << "The file has not been found..." << std::endl;
	}

	Textures[name] = texture;
}

void AssetManager::loadSound(char* name, char* fileName)
{
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(fileName))
	{
		std::cout << "The file has not been found..." << std::endl;
	}

	sf::Sound sound;
	sound.setBuffer(buffer);

	Sounds[name] = sound;
}

void AssetManager::loadMusic(char* name, char* fileName)
{
	sf::Music music;

	if (!music.openFromFile(fileName))
	{
		std::cout << "The file has not been found..." << std::endl;
	}

	Music[name] = music;
}

void AssetManager::loadFont(char* name, char* fileName)
{

}