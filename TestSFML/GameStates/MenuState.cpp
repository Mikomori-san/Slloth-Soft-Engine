#include "stdafx.h"
#include "MenuState.h"
#include "../Manager/MapLoader.h"

void MenuState::init(sf::RenderWindow& rWindow)
{
	this->window.reset(&rWindow, [](sf::RenderWindow*) {});
	MapLoader::getInstance().loadMap(sf::Vector2f());
}

void MenuState::exit()
{
	MapLoader::getInstance().m_layers.clear();
	MapLoader::getInstance().m_tileSetTexture.clear();
}

void MenuState::update(float deltaTime)
{

}

void MenuState::render()
{

	MapLoader::getInstance().drawLayer(*window, MapLoader::getInstance().m_layers[0]); //Background
	MapLoader::getInstance().drawLayer(*window, MapLoader::getInstance().m_layers[1]); //Layer1

}