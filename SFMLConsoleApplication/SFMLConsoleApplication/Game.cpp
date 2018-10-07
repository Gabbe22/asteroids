#include <SFML/Graphics.hpp>
#include <string>

#include "Game.h"
#include "SpaceShip.h"

namespace {
	const std::string windowTitle = "Asteroids";
	const sf::VideoMode videoMode = sf::VideoMode(768, 1024);
	const sf::Color backgroundColor = sf::Color::Black;
	const int FRAMERATE_LIMIT = 60;
	const int START_LEVEL = 1;
	const float SHIP_RADIUS = 20.0f;
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
	//mAsteroidSpawnClock(),
	//mShip(0),
	//mCoin(0),
	//mAsteroids(),
	mLevel(START_LEVEL),
	mGameOver(false)
{
	//createCoin();
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);
	mSpaceShip = std::unique_ptr<SpaceShip>(new SpaceShip(SHIP_VELOCITY, SHIP_RADIUS, getWindowSize()));
}

Game::~Game() {}

void Game::run()
{
	sf::Clock frameClock;
	while (mRenderWindow.isOpen() && !mGameOver) {
		float deltaTime = frameClock.restart().asSeconds();
		handleWindowEvents();
		clearWindow();
		updateShip(deltaTime);
		//updateCoin(deltaTime);
		//updateAsteroids(deltaTime);
		//pruneAsteroids();
		//createAsteroids();
		//handleCoinPickup();
		//handleLostCoin();
		//handleAsteroidCollisions();
		drawShip();
		//drawCoin();
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

void Game::drawShip()
{
	mRenderWindow.draw(*(mSpaceShip.get()));
}

void Game::updateShip(float deltaTime)
{
	mSpaceShip->update(deltaTime);
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
	float shipRadius = ship->getRadius();
	sf::Vector2f coinPosition = coin->getPosition();
	float coinRadius = coin->getRadius();
	return collision(shipPosition, shipRadius, coinPosition, coinRadius);
}