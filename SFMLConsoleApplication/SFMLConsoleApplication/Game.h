#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <vector>

class SpaceShip;
class Coin;

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
	void drawShip();
	void updateShip(float deltaTime);
	//void updateAsteroids(float deltaTime);
	bool collision(sf::Vector2f position0, float radius0, sf::Vector2f position1, float radius1);
	bool collision(SpaceShip* ship, Coin* coin);

	sf::RenderWindow mRenderWindow;
	sf::Texture mShipTexture;
	sf::Texture mCoinTexture;
	sf::Texture mAsteroidTexture;
	std::unique_ptr<SpaceShip> mSpaceShip;
	//Coin *mCoin;
	//Asteroids mAsteroids;
	sf::Clock mAsteroidSpawnClock;
	int mLevel;
	bool mGameOver;

};

#endif
