#ifndef INCLUDED_ASTEROID_H
#define INCLUDED_ASTEROID_H

#include <SFML/Graphics.hpp>
#include "AGameObject.h"

class Asteroid : public sf::Drawable, AGameObject
{
public:
	Asteroid(float velocity, float radius, sf::Vector2f windowSize);
	virtual ~Asteroid();
	sf::FloatRect getBounds() const { return mSprite.getGlobalBounds(); }
	bool shouldBePruned() const { return getBounds().top > static_cast<float>(mWindowSize.y); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);
	void randomSpawn();
	sf::Vector2f getPosition() const
	{
		return mSprite.getPosition();
	}
private:
	void updatePositon(float deltaTime);
	float getRandomX() const;

	const std::string mTextureName = "AsteroidSprite.psd";
	sf::Sprite mSprite;
	sf::Texture mTexture;
	float mVelocity;
	float mRadius;
	sf::Vector2f mWindowSize;
};

#endif
