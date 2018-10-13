#include "Coin.h"
#include <sstream>
#include <iostream>

Coin::Coin(float velocity, float radius, sf::Vector2f windowSize)
	: mVelocity(velocity), mRadius(radius), mWindowSize(windowSize)
{
	if (!mTexture.loadFromFile(mTextureName))
	{
		std::ostringstream ss;
		ss << __FILE__ << "::" << __LINE__ << "::" << __func__ << ": Couldn't open " << mTextureName;
		std::cout << ss.str();
		std::throw_with_nested(std::runtime_error(ss.str().c_str()));
	}
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);
	reset();
}

Coin::~Coin()
{
}

void Coin::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Coin::update(float deltaTime)
{
	updatePosition(deltaTime);
}

bool Coin::isLost() const
{
	if (mSprite.getPosition().y > mWindowSize.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Coin::reset()
{
	mSprite.setPosition(sf::Vector2f(getRandomX(), -2 * mRadius));
}

float Coin::getRandomX() const
{
	int width = static_cast<int>(mWindowSize.x);
	float x = rand() % width + 1 - 2 * mRadius;
	return x;
}

void Coin::updatePosition(float deltaTime)
{
	sf::Vector2f direction(0.0f, 1.0f);
	mSprite.move(deltaTime * mVelocity * direction);
}