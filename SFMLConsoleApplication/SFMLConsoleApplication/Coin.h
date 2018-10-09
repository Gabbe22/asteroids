#ifndef INCLUDED_COIN_H
#define INCLUDED_COIN_H

#include <SFML/Graphics.hpp>
#include "AGameObject.h"

class Coin : public sf::Drawable, AGameObject
{
public:
	Coin(float velocity, float radius, sf::Vector2f windowSize);
	virtual ~Coin();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);
	bool isLost() const;
	void reset();
	sf::Vector2f getPosition() const
	{
		return mSprite.getPosition();
	}
private:
	void updatePosition(float deltaTime);
	float getRandomX() const;

	const std::string mTextureName = "CoinSprite.psd";
	sf::Sprite mSprite;
	sf::Texture mTexture;
	float mVelocity;
	float mRadius;
	sf::Vector2f mWindowSize;
};

#endif