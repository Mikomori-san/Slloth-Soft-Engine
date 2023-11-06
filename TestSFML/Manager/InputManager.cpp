#include "InputManager.h"

void InputManager::init(sf::Window& window)
{
	window.setKeyRepeatEnabled(false);
	
	isKeyDown[sf::Keyboard::Key::W] = false;
	isKeyDown[sf::Keyboard::Key::A] = false;
	isKeyDown[sf::Keyboard::Key::S] = false;
	isKeyDown[sf::Keyboard::Key::D] = false;
	isKeyDown[sf::Keyboard::Key::Space] = false;
	isKeyDown[sf::Keyboard::Key::Num1] = false;
	isKeyDown[sf::Keyboard::Key::Num2] = false;

	isKeyUp[sf::Keyboard::Key::W] = false;
	isKeyUp[sf::Keyboard::Key::A] = false;
	isKeyUp[sf::Keyboard::Key::S] = false;
	isKeyUp[sf::Keyboard::Key::D] = false;
	isKeyUp[sf::Keyboard::Key::Space] = false;
	isKeyUp[sf::Keyboard::Key::Num1] = false;
	isKeyUp[sf::Keyboard::Key::Num2] = false;

	isKeyPressed[sf::Keyboard::Key::W] = false;
	isKeyPressed[sf::Keyboard::Key::A] = false;
	isKeyPressed[sf::Keyboard::Key::S] = false;
	isKeyPressed[sf::Keyboard::Key::D] = false;
	isKeyPressed[sf::Keyboard::Key::Space] = false;
	isKeyPressed[sf::Keyboard::Key::Num1] = false;
	isKeyPressed[sf::Keyboard::Key::Num2] = false;
}

void InputManager::update()
{
	for(auto iteration = isKeyDown.begin(); iteration != isKeyDown.end(); ++iteration)
	{
		isKeyDown[iteration->first] = false;
	}

	for (auto iteration = isKeyUp.begin(); iteration != isKeyUp.end(); ++iteration)
	{
		isKeyUp[iteration->first] = false;
	}
}

bool InputManager::getKeyPressed(sf::Keyboard::Key key)
{
	return isKeyPressed[key] ? isKeyPressed[key] : false;
}

bool InputManager::getKeyDown(sf::Keyboard::Key key)
{
	return isKeyDown[key] ? isKeyDown[key] : false;
}

bool InputManager::getKeyUp(sf::Keyboard::Key key)
{
	return isKeyUp[key] ? isKeyUp[key] : false;
}

void InputManager::handleEvents(sf::Event& event)
{
	if (event.type == sf::Event::EventType::KeyPressed)
	{
		isKeyDown[event.key.code] = true;
		isKeyPressed[event.key.code] = true;
	}
	else if (event.type == sf::Event::EventType::KeyReleased)
	{
		isKeyUp[event.key.code] = true;
		isKeyPressed[event.key.code] = false;
	}
}