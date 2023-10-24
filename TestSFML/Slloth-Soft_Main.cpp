// TestSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Window.hpp>
#include "Manager/AssetManager.h"

int main()
{
	AssetManager::instance().loadMusic("something", "H:/Privat/HMMMMM.mp3");
	AssetManager::instance().Music["something"]->play();
	
}
