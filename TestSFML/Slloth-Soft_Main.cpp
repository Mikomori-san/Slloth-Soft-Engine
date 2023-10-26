// TestSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Window.hpp>
#include "Manager/AssetManager.h"
#include "Game.h"
#include <filesystem>

int main()
{
	
	std::cout << "Press ESC to close the window" << std::endl;
	Game game;
	game.run();
	std::cout << "All done" << std::endl;
}
