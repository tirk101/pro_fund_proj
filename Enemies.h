#ifndef ENEMIES_H
#define ENEMIES_H

#pragma once

#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"

class Enemies
{
private:
	//Slime
	sf::Sprite slime;
	sf::Texture slimeTex;
	sf::IntRect currentFrameSlime;
	sf::Clock animTimerSlime;
	float movementSpeedSlime;
	int enemyType;

	void initTexture();
	void initAnimation();
	void initEnemiesType();
	void initSprite();
public:
	Enemies(int type, float posX, float posY);
	virtual ~Enemies();

	//Accessor
	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPosition() const;
	const int getDamagetoHp() const;
	const int getHpEnemy() const;

	void updatesAnimation();
	void updatesMovement();
	void updates();
	void render(sf::RenderTarget& target);
};

#endif // !ENEMIES_H