#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>

#include "Game.h"
#include "SpaceShip.h"
#include "Coin.h"
#include "Asteroid.h"

namespace {
	const std::string windowTitle = "Asteroids";
	const sf::VideoMode videoMode = sf::VideoMode(768, 900);
	const sf::Color backgroundColor = sf::Color::Black;
	const int FRAMERATE_LIMIT = 60;
	const int START_LEVEL = 1;
	const float SHIP_RADIUS = 21.0f;
	const float SHIP_VELOCITY = 400.0f;
	const float COIN_RADIUS = 16.0f;
	const float COIN_VELOCITY = 80.0f;
	const float ASTEROID_RADIUS = 32.0f;
	const float ASTEROID_SPAWN_DELTA = 1.0f;
	const float ASTEROID_SPAWN_COUNT_BASE = 1.0f;
	const float ASTEROID_SPAWN_COUNT_INCREMENT = 0.5f;
	const float ASTEROID_MIN_VELOCITY = 80.0f;
	const float ASTEROID_DELTA_VELOCITY = 200.0f;
}

Game::Game() :
	mRenderWindow(videoMode, windowTitle, sf::Style::Titlebar | sf::Style::Close),
	//mShipTexture(loadTexture("ShipSprite.psd")),
	//mCoinTexture(loadTexture("CoinSprite.psd")),
	//mAsteroidTexture(loadTexture("AsteroidSprite.psd")),
	mAsteroidSpawnClock(),
	//mShip(0),
	Asteroids(),
	mLevel(START_LEVEL),
	mGameOver(false)
{
	srand(static_cast<unsigned int>(time(NULL)));
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);
	mSpaceShip = std::unique_ptr<SpaceShip>(new SpaceShip(SHIP_VELOCITY, SHIP_RADIUS, getWindowSize()));
	mCoin = std::unique_ptr<Coin>(new Coin(COIN_VELOCITY, COIN_RADIUS, getWindowSize()));
	//mAsteroid = std::unique_ptr<Asteroid>(new Asteroid(ASTEROID_MIN_VELOCITY, ASTEROID_RADIUS, getWindowSize()));
}

Game::~Game() {}

void Game::run()
{
	sf::Clock frameClock;
	while (mRenderWindow.isOpen() && !mGameOver) {
		float deltaTime = frameClock.restart().asSeconds();
		handleWindowEvents();
		clearWindow();
		mSpaceShip->update(deltaTime);
		mCoin->update(deltaTime);
		//mAsteroid->update(deltaTime);
		updateAsteroids(deltaTime);
		//pruneAsteroids();
		createAsteroids();
		handleCoinPickup();
		handleLostCoin();
		handleAsteroidCollision();
		mRenderWindow.draw(*(mSpaceShip.get()));
		mRenderWindow.draw(*(mCoin.get()));
		for (AsteroidVector::size_type i = 0; i < Asteroids.size(); i++)
		{
			mRenderWindow.draw(*(Asteroids[i].get()));
		}
		//drawAsteroids();
		displayWindow();
	}
}

sf::Vector2f Game::getWindowSize()
{
	auto windowSize = mRenderWindow.getSize();
	return sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
}

void Game::handleWindowEvents()
{
	sf::Event event;
	while (mRenderWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mRenderWindow.close();
		}
	}
}

void Game::clearWindow()
{
	mRenderWindow.clear(backgroundColor);
}

void Game::displayWindow()
{
	mRenderWindow.display();
}

void Game::createAsteroids()
{
	if (ASTEROID_SPAWN_DELTA < mAsteroidSpawnClock.getElapsedTime().asSeconds())
	{
		int spawnCount = int(ASTEROID_SPAWN_COUNT_BASE + mLevel * ASTEROID_SPAWN_COUNT_INCREMENT);
		for (int i = 0; i < spawnCount; i++)
		{
			Asteroid *asteroid = new Asteroid(ASTEROID_MIN_VELOCITY, ASTEROID_RADIUS, getWindowSize());
			Asteroids.push_back(*asteroid);
		}
		mAsteroidSpawnClock.restart();
	}
}

void Game::handleCoinPickup()
{
	if (collision(mSpaceShip.get(), mCoin.get()))
	{
		mCoin->reset();
	}
}

void Game::handleLostCoin()
{
	if (mCoin->isLost())
		mGameOver = true;
}

void Game::updateAsteroids(float deltaTime)
{
	for (AsteroidVector::size_type i = 0; i < Asteroids.size(); i++)
	{
		Asteroids[i]->update(deltaTime);
	}
}

void Game::handleAsteroidCollision()
{
	for (AsteroidVector::size_type i = 0; i < Asteroids.size(); i++)
	{
		if (collision(mSpaceShip.get(), Asteroids[i].get()))
		{
			mGameOver = true;
		}
	}
}

bool Game::collision(sf::Vector2f position0, float radius0, sf::Vector2f position1, float radius1)
{
	float deltaX = position0.x - position1.x;
	float deltaY = position0.y - position1.y;
	float radiusSum = radius0 + radius1;
	return deltaX * deltaX + deltaY * deltaY < radiusSum * radiusSum;
}

bool Game::collision(SpaceShip *ship, Coin *coin)
{
	sf::Vector2f shipPosition = ship->getPosition();
	sf::Vector2f coinPosition = coin->getPosition();
	return collision(shipPosition, SHIP_RADIUS, coinPosition, COIN_RADIUS);
}

bool Game::collision(SpaceShip *ship, Asteroid *asteroid)
{
	sf::Vector2f shipPosition = ship->getPosition();
	sf::Vector2f asteroidPosition = asteroid->getPosition();
	return collision(shipPosition, SHIP_RADIUS, asteroidPosition, ASTEROID_RADIUS);
}