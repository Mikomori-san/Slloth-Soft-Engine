#pragma once

#include <SFML/Window.hpp>
#include <map>

class InputManager
{
public:
	
	static InputManager& instance()
	{
		static InputManager instance;
		return instance;
	}

	void init(sf::Window& window);
	void update();
	bool getKeyPressed(sf::Keyboard::Key key);
	bool getKeyDown(sf::Keyboard::Key key);
	bool getKeyUp(sf::Keyboard::Key key);
	void handleEvents(sf::Event& event);

private:

	std::map<sf::Keyboard::Key, bool> isKeyDown = std::map<sf::Keyboard::Key, bool>{};
	std::map<sf::Keyboard::Key, bool> isKeyPressed = std::map<sf::Keyboard::Key, bool>{};
	std::map<sf::Keyboard::Key, bool> isKeyUp = std::map<sf::Keyboard::Key, bool>{};
};