#include "SpaceShip.h"
#include <sstream>
#include <iostream>

SpaceShip::SpaceShip(float velocity, float radius, sf::Vector2f windowSize)
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
	//mSprite.SetCenter();

	mSprite.setPosition(sf::Vector2f(100, 200));
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void SpaceShip::update(float deltaTime)
{
	updatePosition(deltaTime);
	constrainPosition();
}

void SpaceShip::updatePosition(float deltaTime)
{
	float directionX = 0.0f;
	float directionY = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		directionX -= 1.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		directionX = 1.0f;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		directionY -= 1.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		directionY = 1.0f;
	
	sf::Vector2f direction(directionX, directionY);
	mSprite.move(deltaTime * mVelocity * direction);
}

void SpaceShip::constrainPosition()
{
	float minX = mRadius;
	float minY = mRadius;
	float maxX = mWindowSize.x - mRadius;
	float maxY = mWindowSize.y - mRadius;
	float shipX = mSprite.getPosition().x;
	float shipY = mSprite.getPosition().y;
	
	if (shipX < minX)
		shipX = minX;
	else if (maxX < shipX)
		shipX = maxX;
	
	if (shipY < minY)
		shipY = minY;
	else if (maxY < shipY)
		shipY = maxY;

	sf::Vector2f shipPosition(shipX, shipY);
	mSprite.setPosition(shipPosition);
}