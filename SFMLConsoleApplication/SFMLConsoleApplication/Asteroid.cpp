#include "Asteroid.h"
#include <sstream>
#include <iostream>

Asteroid::Asteroid()
{
	if (!m_texture.loadFromFile(m_textureName))
	{
		std::ostringstream ss;
		ss << __FILE__ << "::" << __LINE__ << "::" << __func__ << ": Couldn't open " << m_textureName;
		std::cout << ss.str();
		std::throw_with_nested(std::runtime_error(ss.str().c_str()));
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	
	m_position = sf::Vector2f(100, 200);
	m_sprite.setPosition(m_position);
}

Asteroid::~Asteroid()
{
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

void Asteroid::update(float deltaTime)
{
	updatePositon(deltaTime);
}

void Asteroid::updatePositon(float deltaTime)
{
	
}