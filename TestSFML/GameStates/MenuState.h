#pragma once
#include "GameState.h"

class MenuState : public GameState
{
public:
	void init(sf::RenderWindow& rWindow) override;
	void exit() override;
	void update(float deltaTime) override;
	void render() override;
private:
	std::shared_ptr<sf::RenderWindow> window;
};