#pragma once
#include "GraphicsCP.h"
#include "../../Enums/Animationtype.h"

class AnimatedGraphicsCP : public GraphicsCP {
public:
    AnimatedGraphicsCP(std::weak_ptr<GameObject> gameObject, std::string id, std::weak_ptr<sf::RenderWindow> renderWindow, const sf::Texture& texture, std::vector<int> animationTypeFramesCountVar, float animationSpeed)
        : GraphicsCP(gameObject, id, texture), window(renderWindow), animationTypeFramesCount(animationTypeFramesCountVar), ANIMATION_SPEED(animationSpeed),
            TILING_X([this]() {
                int max = 0;
                for (auto& it : animationTypeFramesCount)
                {
                    if (it > max)
                        max = it;
                }
                return max;
            }()), 
            TILING_Y(animationTypeFramesCount.size())
    {}

    std::string getComponentId() override { return componentId; }
    void setComponentId(std::string id) override { this->componentId = id; }
    void init() override;
    void update(float deltaTime) override;
    void draw() override;
    void setSprite(std::shared_ptr<sf::Texture> texture) override;
    void setAnimationType(Animationtype type);
    sf::Sprite& getSprite() { return *sprite; }
    
private:
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<int> animationTypeFramesCount;
    Animationtype m_animationType = Animationtype::IdleDown; //All GameObjects with Sprites got IdleDown and stuff, trust me :)
    float animationTimeIndex = 0;
    const float ANIMATION_SPEED;
    const int TILING_X;
    const int TILING_Y;
    void doAnimation();
    void handleIdle();
};