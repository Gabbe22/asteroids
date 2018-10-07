#ifndef INCLUDED_ASTEROID_H
#define INCLUDED_ASTEROID_H

#include <SFML/Graphics.hpp>
#include "AGameObject.h"

class Asteroid : public sf::Drawable, AGameObject
{
public:
	Asteroid();
	virtual ~Asteroid();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);

private:
	void updatePositon(float deltaTime);

	const std::string m_textureName = "AsteroidSprite.psd";
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	float mVelocity;
	float mRadius;
	//sf::VertexArray m_vertices;

	sf::Vector2f m_position;
};

#endif
