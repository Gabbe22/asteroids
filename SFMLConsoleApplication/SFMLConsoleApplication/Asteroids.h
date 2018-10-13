#ifndef INCLUDED_ASTEROIDS_H
#define INCLUDED_ASTEROIDS_H

#include "Asteroid.h"
#include <vector>

class Asteroids
{
public:
	Asteroids();
	void addAsteroid(Asteroid asteroid);
private:
	typedef std::vector<Asteroid> AsteroidVector;
	AsteroidVector mAsteroids;
};

#endif