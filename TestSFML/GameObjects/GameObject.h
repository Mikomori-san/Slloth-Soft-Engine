#include<SFML/Graphics.hpp>


class GameObject : public sf::Transformable
{
public:
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
};