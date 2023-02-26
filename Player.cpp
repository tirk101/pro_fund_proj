#include "Player.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	
	for (int i = 0; i < 4; i++)
	{
		this->checkMap[i] = false;
	}

	//Animation ATK
	this->atkking = false;
	this->diffTimer = 0;
	this->dirPlayer = 2;
	this->animAtkFrame = 1;

	//ATK Cooldown
	this->atkCDMax = 20.f;
	this->atkCD = atkCDMax;
}

//Private functions
void Player::initTexture()
{
	//Load a texture form file
	if (!this->texture.loadFromFile("Texture/Player/Archer.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 896, 64, 64);
	this->sprite.setTextureRect(this->currentFrame);
	
	//Resize the sprite
	this->sprite.scale(playerScaleX, playerScaleY);
	
	//Set position
	this->playerPosX = 900.f;
	this->playerPosY = 800.f;
	this->sprite.setPosition(this->playerPosX, this->playerPosY);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
}

//Con/Des
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Player::~Player()
{
}

const int Player::DirPlayer() const
{
	return this->dirPlayer;
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const bool Player::canAttack()
{
	if (this->atkking == true && this->atkCD >= this->atkCDMax)
	{
		this->atkCD = 0.f;
		return true;
	}
	else return false;
}


void Player::updateCondition()
{
	//TOP
	if (this->sprite.getPosition().y <= 200 && (this->sprite.getPosition().x <= 825 || this->sprite.getPosition().x >= 1000))
	{
		if (this->sprite.getPosition().y < 195 && this->sprite.getPosition().x < 825)
		{
			this->checkMap[1] = true;
		}
		else if (this->sprite.getPosition().y < 195 && this->sprite.getPosition().x > 1000)
		{
			this->checkMap[3] = true;
		}
		else this->checkMap[0] = true;
	}

	//LEFT
	if (this->sprite.getPosition().x <= 478 && (this->sprite.getPosition().y <= 580 || this->sprite.getPosition().y >= 720))
	{
		if (this->sprite.getPosition().x < 475 && this->sprite.getPosition().y < 580)
		{
			this->checkMap[0] = true;
		}
		else if (this->sprite.getPosition().x < 475 && this->sprite.getPosition().y > 720)
		{
			this->checkMap[2] = true;
		}
		else this->checkMap[1] = true;
	}
	
	//Under
	if (this->sprite.getPosition().y >= 850 && (this->sprite.getPosition().x <= 825 || this->sprite.getPosition().x >= 1000))
	{
		if (this->sprite.getPosition().y > 855 && this->sprite.getPosition().x < 825)
		{
			this->checkMap[1] = true;
		}
		else if (this->sprite.getPosition().y > 855 && this->sprite.getPosition().x > 995)
		{
			this->checkMap[3] = true;
		}
		else this->checkMap[2] = true;
	}

	//RIGHT
	if (this->sprite.getPosition().x >= 1340 && (this->sprite.getPosition().y <= 460 || this->sprite.getPosition().y >= 590))
	{
		if (this->sprite.getPosition().x > 1345 && this->sprite.getPosition().y < 460)
		{
			this->checkMap[0] = true;
		}
		else if (this->sprite.getPosition().x > 1345 && this->sprite.getPosition().y > 590)
		{
			this->checkMap[2] = true;
		}
		else this->checkMap[3] = true;
	}

	//Portal
	if (this->sprite.getPosition().x >= 850 && this->sprite.getPosition().x <= 950 && this->sprite.getPosition().y >= 455 && this->sprite.getPosition().y <= 580)
	{
		if (this->sprite.getPosition().x > 845 && this->sprite.getPosition().x < 855) this->checkMap[3] = true;
		else if (this->sprite.getPosition().x > 945 && this->sprite.getPosition().x < 955) this->checkMap[1] = true;
		else if (this->sprite.getPosition().y > 450 && this->sprite.getPosition().y < 460) this->checkMap[2] = true;
		else if (this->sprite.getPosition().y > 575 && this->sprite.getPosition().y < 585) this->checkMap[0] = true;
	}
}

void Player::updateAttacking()
{
	//Attacking
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->atkking = true;
	}

	//ATK CD
	if (this->atkCD < this->atkCDMax)
		this->atkCD += 0.5f;
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	//Walk
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->sprite.getPosition().y > 0 && this->checkMap[0] == false)
	{
		this->sprite.move(movementSpeed * 0.f, movementSpeed * -1.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_UP;
		this->playerPosX = this->sprite.getPosition().x;
		this->playerPosY = this->sprite.getPosition().y;
		this->dirPlayer = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->sprite.getPosition().x > 0 && this->checkMap[1] == false)
	{
		this->sprite.move(movementSpeed * -1.f, movementSpeed * 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		this->playerPosX = this->sprite.getPosition().x;
		this->playerPosY = this->sprite.getPosition().y;
		this->dirPlayer = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->sprite.getPosition().y < 980 && this->checkMap[2] == false)
	{
		this->sprite.move(movementSpeed * 0.f, movementSpeed * 1.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
		this->playerPosX = this->sprite.getPosition().x;
		this->playerPosY = this->sprite.getPosition().y;
		this->dirPlayer = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->sprite.getPosition().x < 1835 && this->checkMap[3] == false)
	{
		this->sprite.move(movementSpeed * 1.f, movementSpeed * 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		this->playerPosX = this->sprite.getPosition().x;
		this->playerPosY = this->sprite.getPosition().y;
		this->dirPlayer = 3;
	}
}

void Player::updateMoveAnim()
{
	//IDLE
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	} 

	//MOVING LEFT
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT && this->sprite.getPosition().x > 0)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 576.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 512.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	//MOVING RIGHT
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT && this->sprite.getPosition().x < 1835)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 704.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 512.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	//MOVING UP
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_UP && this->sprite.getPosition().y > 0)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 512.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 512.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	//MOVING DOWN
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_DOWN && this->sprite.getPosition().y < 980)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 640.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 512.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
}

void Player::updateATKAnim()
{
	//Top
	if (this->atkking == true && this->dirPlayer == 0)
	{
		this->diffTimer++;
		if (this->diffTimer == 10)
		{
			this->animAtkFrame++;
			this->currentFrame.top = 1024.f;
			this->currentFrame.left += (64.f * this->animAtkFrame);
			if (this->currentFrame.left >= 832.f)
			{
				this->currentFrame.left = 0;
			}
			this->sprite.setTextureRect(this->currentFrame);
			this->diffTimer = 0;
		}
		if (this->animAtkFrame == 5)
		{
			this->animAtkFrame = 1;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			this->atkking = false;
		}
	}
	
	//LEFT
	if (this->atkking == true && this->dirPlayer == 1)
	{
		this->diffTimer++;
		if (this->diffTimer == 10)
		{
			this->animAtkFrame++;
			this->currentFrame.top = 1088.f;
			this->currentFrame.left += (64.f * this->animAtkFrame);
			if (this->currentFrame.left >= 832.f)
			{
				this->currentFrame.left = 0;
			}
			this->sprite.setTextureRect(this->currentFrame);
			this->diffTimer = 0;
		}
		if (this->animAtkFrame == 5)
		{
			this->animAtkFrame = 1;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			this->atkking = false;
		}
	}

	//Under
	if (this->atkking == true && this->dirPlayer == 2)
	{
		this->diffTimer++;
		if (this->diffTimer == 10)
		{
			this->animAtkFrame++;
			this->currentFrame.top = 1152.f;
			this->currentFrame.left += (64.f * this->animAtkFrame);
			if (this->currentFrame.left >= 832.f)
			{
				this->currentFrame.left = 0;
			}
			this->sprite.setTextureRect(this->currentFrame);
			this->diffTimer = 0;
		}
		if (this->animAtkFrame == 5)
		{
			this->animAtkFrame = 1;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			this->atkking = false;
		}
	}

	//RIGHT
	if (this->atkking == true && this->dirPlayer == 3)
	{
		this->diffTimer++;
		if (this->diffTimer == 10)
		{
			this->animAtkFrame++;
			this->currentFrame.top = 1216.f;
			this->currentFrame.left += (64.f * this->animAtkFrame);
			if (this->currentFrame.left >= 832.f)
			{
				this->currentFrame.left = 0;
			}
			this->sprite.setTextureRect(this->currentFrame);
			this->diffTimer = 0;
		}
		if (this->animAtkFrame == 5)
		{
			this->animAtkFrame = 1;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			this->atkking = false;
		}
	}
}

//Functions
void Player::update()
{
	this->updateCondition();
	this->updateMovement();
	this->updateAttacking();
	this->updateATKAnim();
	this->updateMoveAnim();
	for (int i = 0; i < 4; i++)
	{
		this->checkMap[i] = false;
	}
}

