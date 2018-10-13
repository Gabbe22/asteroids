#include "Asteroids.h"

Asteroids::Asteroids():
	mAsteroids(){
}

void Asteroids::addAsteroid(Asteroid asteroid)
{
	mAsteroids.push_back(asteroid);
}