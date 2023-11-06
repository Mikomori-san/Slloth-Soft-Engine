#pragma once
#include "../GameStates/GameState.h"
#include <map>
#include <string>
#include <memory>

class GameStateManager
{
public:

    static GameStateManager& getInstance()
    {
        static GameStateManager instance;
        return instance;
    }

    void reg(std::string name, GameState* state);
    void setState(std::string name);
    void update(float deltaTime);
    void render();

private:
    GameStateManager() {}
    ~GameStateManager() {}
    GameStateManager(const GameStateManager&) = delete;
    GameStateManager& operator= (const GameStateManager&) = delete;

    std::unique_ptr<GameState> currentState;
    std::map<std::string, std::unique_ptr<GameState>> states;
};