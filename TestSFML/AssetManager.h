#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:
	std::map<char*, sf::Texture> Textures = std::map<char*, sf::Texture>{};
	std::map<char*, sf::Sound> Sounds = std::map<char*, sf::Sound>{};
	std::map<char*, sf::Music> Music = std::map<char*, sf::Music>{};
	std::map<char*, sf::Font> Fonts = std::map<char*, sf::Font>{};

	void loadTexture(char* name, char* fileName);
	void loadSound(char* name, char* fileName);
	void loadMusic(char* name, char* fileName);
	void loadFont(char* name, char* fileName);

private:
	AssetManager() = delete;
};