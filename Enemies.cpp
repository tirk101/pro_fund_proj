#include "Enemies.h"

void Enemies::initTexture()
{
	if (!this->slimeTex.loadFromFile("Texture/Enemies/slimej.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Enemies::initAnimation()
{
	this->animTimerSlime.restart();
}

void Enemies::initEnemiesType()
{
	if (this->enemyType == 1)
	{
		this->movementSpeedSlime = 2.f;
		this->slime.setScale(3.5f, 3.5f);
	}
	if (this->enemyType == 2)
	{
		this->movementSpeedSlime = 1.f;
		this->slime.setScale(6.5f, 6.5f);
		this->slime.setColor(sf::Color::Green);
	}
	if (this->enemyType == 3)
	{
		this->movementSpeedSlime = 5.f;
		this->slime.setScale(2.5f, 2.5f);
		this->slime.setColor(sf::Color::Red);
	}
}

void Enemies::initSprite()
{
	this->slime.setTexture(this->slimeTex);
	this->currentFrameSlime = sf::IntRect(0, 0, 32, 19);
	this->slime.setTextureRect(this->currentFrameSlime);
}

Enemies::Enemies(int type, float posX, float posY)
{
	this->slime.setPosition(posX, posY);
	
	this->enemyType = type;

	//Initialize
	this->initTexture();
	this->initSprite();
	this->initEnemiesType();
	this->initAnimation();
}

Enemies::~Enemies()
{
}

const sf::FloatRect Enemies::getBounds() const
{
	return this->slime.getGlobalBounds();
}

const sf::Vector2f& Enemies::getPosition() const
{
	return this->slime.getPosition();
}

const int Enemies::getDamagetoHp() const
{
	if (this->enemyType == 1) return 3;
	else if (this->enemyType == 2) return 5;
	else if (this->enemyType == 3) return 1;
}

const int Enemies::getHpEnemy() const
{
	if (this->enemyType == 2) return 2;
	else return 1;
}

void Enemies::updatesAnimation()
{
	if (this->animTimerSlime.getElapsedTime().asSeconds() >= 0.075f)
	{
		this->currentFrameSlime.left += 32.f;
		if (this->currentFrameSlime.left > 224.f)
		{
			this->currentFrameSlime.left = 0;
		}
		this->animTimerSlime.restart();
		this->slime.setTextureRect(this->currentFrameSlime);
	}
}

void Enemies::updatesMovement()
{
	//std::cout << this->player->posPlayerX() << " , " << this->player->posPlayerY() << std::endl;
	if (this->slime.getPosition().x < 465) this->slime.move(this->movementSpeedSlime * 1.f, 0.f);
	else if (this->slime.getPosition().y < 225) this->slime.move(0.f, this->movementSpeedSlime * 1.f);
	else if (this->slime.getPosition().x > 1400) this->slime.move(this->movementSpeedSlime * -1.f, 0.f);
	else if (this->slime.getPosition().y > 920) this->slime.move(0.f, this->movementSpeedSlime * -1.f);
	else
	{
		if (this->slime.getPosition().x <= 900.f)
		{
			this->slime.move(this->movementSpeedSlime * 1.f, 0);
		}
		else if (this->slime.getPosition().x > 900.f)
		{
			this->slime.move(this->movementSpeedSlime * -1.f, 0);
		}
		if (this->slime.getPosition().y <= 540.f)
		{
			this->slime.move(0, this->movementSpeedSlime * 1.f);
		}
		else if (this->slime.getPosition().y > 540.f)
		{
			this->slime.move(0, this->movementSpeedSlime * -1.f);
		}
	}
	
}

void Enemies::updates()
{
	this->updatesAnimation();
	this->updatesMovement();
}

void Enemies::render(sf::RenderTarget& target)
{
	target.draw(this->slime);
}
