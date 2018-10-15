#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <vector>

class SpaceShip;
class Coin;
class Asteroid;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::Vector2f getWindowSize();
	void handleWindowEvents();
	void clearWindow();
	void displayWindow();
	void handleCoinPickup();
	void handleLostCoin();
	void handleAsteroidCollision(const Asteroid* pAsteroid);
	void pruneAsteroids();
	void createAsteroids();
	void updateAsteroid(float deltaTime, Asteroid* pAsteroid) const;
	bool collision(sf::Vector2f position0, float radius0, sf::Vector2f position1, float radius1);
	bool collision(SpaceShip* ship, Coin* coin);
	bool collision(const SpaceShip* ship, const Asteroid* asteroid);

	sf::RenderWindow mRenderWindow;
	sf::Texture mShipTexture;
	sf::Texture mCoinTexture;
	sf::Texture mAsteroidTexture;
	std::unique_ptr<SpaceShip> mSpaceShip;
	std::unique_ptr<Coin> mCoin;
	std::vector<std::unique_ptr<Asteroid>> mAsteroids;
	sf::Clock mAsteroidSpawnClock;
	int mLevel;
	bool mGameOver;

};

#endif
