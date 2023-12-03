#include "stdafx.h"
#include "GameplayState.h"
#include "../Components/Graphics_Components/AnimatedGraphicsCP.h"
#include "../Components/Transformation_Components/TransformationCP.h"
#include "../Components/Input_Components/MovementInputWASDCP.h"
#include "../Components/Input_Components/MovementInputArrowsCP.h"
#include "../Components/Collision_Components/RectCollisionCP.h"
#include "../Components/Graphics_Components/RenderCP.h"

void GameplayState::init(sf::RenderWindow& rWindow)
{
    this->window.reset(&rWindow, [](sf::RenderWindow*) {});

    this->player = std::make_shared<GameObject>("Player");
    this->player2 = std::make_shared<GameObject>("Player2");

    addPlayerComponents(player, true);
    addPlayerComponents(player2, false);

    setPositionForPlayer(player);
    setPositionForPlayer(player2);

    DebugDraw::getInstance().initialize(*window);

    AssetManager::getInstance().loadSound("CompleteSound", "Assets\\Sounds\\completeSound.wav");
    AssetManager::getInstance().loadMusic("MusicTrack", "Assets\\Music\\musicTrack.ogg");
    AssetManager::Music["MusicTrack"]->play();

    for (auto& gameObject : gameObjects)
    {
        gameObject->init();
    }
}

void GameplayState::exit()
{
    for (auto gameObject : gameObjects)
    {
        gameObject.reset();
    }
    gameObjects.clear();

    this->player.reset();
    this->player2.reset();
    this->window.reset();
    DebugDraw::getInstance().unload();

    AssetManager::getInstance().unloadAssets();
}

void GameplayState::update(float deltaTime)
{
    for (auto gameObject : gameObjects)
        gameObject->update(deltaTime);

    checkAreaBorders();
}

void GameplayState::render()
{
    drawFloor(sf::Vector2f(0, 0),
        sf::Vector2i(static_cast<int>(window->getSize().x / TILE_SIZE) + 1, static_cast<int>(window->getSize().y / TILE_SIZE + 1)),
        sf::Vector2i(TILE_SIZE, TILE_SIZE));

    for (auto& gameObject : gameObjects)
    {
        for (auto& component : gameObject->getComponentsOfType<RenderCP>())
        {
            component->draw();
        }
    }
}

void GameplayState::checkAreaBorders()
{
    // Hier könnte die Logik stehen, um die Grenzbereiche für jeden Spieler zu überprüfen.
    // Sie sollten dies für beide Spieler tun (player und player2).
}

void GameplayState::drawFloor(sf::Vector2f position, sf::Vector2i tiles, sf::Vector2i tileSize)
{
    for (auto x = 0; x < tiles.x; x++)
    {
        for (auto y = 0; y < tiles.y; y++)
        {
            auto tilepos = sf::Vector2f(position.x + x * tileSize.x, position.y + y * tileSize.y);
            DebugDraw::getInstance().drawRectangle(tilepos, tileSize.x, tileSize.y, (x + y) % 2 == 0 ? sf::Color::White : sf::Color::Black);
        }
    }
}

void GameplayState::setPositionForPlayer(std::shared_ptr<GameObject> player)
{
    std::shared_ptr<TransformationCP> playerTransf = std::dynamic_pointer_cast<TransformationCP>(player->getComponent("PlayerTransformationCP"));
    playerTransf->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
    gameObjects.push_back(player);
}

void GameplayState::addPlayerComponents(std::shared_ptr<GameObject> player, bool useArrowKeys)
{
    const int PLAYER_ANIMATION_SPEED = 8;
    if (AssetManager::getInstance().Textures.find("PlayerTexture") == AssetManager::getInstance().Textures.end()) {
        AssetManager::getInstance().loadTexture("PlayerTexture", "Assets\\Textures\\playerSpriteSheet.png");
    }
    std::vector<int> playerSpriteSheetAnimationCounts = { 3, 3, 1, 3, 10, 10, 10, 10 };

    std::shared_ptr<AnimatedGraphicsCP> playerGraphicsCP = std::make_shared<AnimatedGraphicsCP>(
        player, "PlayerSpriteCP", *AssetManager::getInstance().Textures.at("PlayerTexture"), playerSpriteSheetAnimationCounts, PLAYER_ANIMATION_SPEED
    );

    player->addComponent(playerGraphicsCP);

    const float
