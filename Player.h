#pragma once

enum PLAYER_ANIMATION_STATES 
{ 
	IDLE = 0, 
	MOVING_LEFT, 
	MOVING_RIGHT, 
	MOVING_UP, 
	MOVING_DOWN,
	ATKUP,
	ATKLEFT,
	ATKDOWN,
	ATKRIGHT
};

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	//Player
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock animationTimer;

	//Check Wall
	bool checkMap[4];

	//Size sprite
	float playerScaleX = 1.5f;
	float playerScaleY = 1.5f;

	//Movement
	float movementSpeed = 3.f;
	
	//Animation
	short animState;
	sf::IntRect currentFrame;
	
	//Pos
	int dirPlayer;
	float playerPosX;
	float playerPosY;

	//ATK
	bool atkking;
	int diffTimer;
	int animAtkFrame;

	//Cooldown ATK
	float atkCD;
	float atkCDMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
public:
	
	Player();
	virtual ~Player();

	//Send Functions
	const int DirPlayer() const;
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const bool canAttack();

	//Functions
	void updateCondition();
	void updateAttacking();
	void updateMovement();
	void updateMoveAnim();
	void updateATKAnim();
	void update();
	void render(sf::RenderTarget& target)
	{
		target.draw(this->sprite);
	}
};

