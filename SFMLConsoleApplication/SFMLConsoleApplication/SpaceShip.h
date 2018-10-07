#ifndef INCLUDED_SPACESHIP_H
#define INCLUDED_SPACESHIP_H

#include <SFML/Graphics.hpp>
#include "IMovable.h"

class SpaceShip : public sf::Drawable, IGameObject
{
public:
	SpaceShip(float velocity, float radius, sf::Vector2f windowSize);
	virtual ~SpaceShip();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);

private:
	void updatePosition(float deltaTime);
	void constrainPosition();

	const std::string mTextureName = "ShipSprite.psd";
	sf::Sprite mSprite;
	sf::Texture mTexture;
	float mVelocity;
	float mRadius;
	sf::Vector2f mWindowSize;
};

#endif