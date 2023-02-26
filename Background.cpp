#include "Background.h"

void Background::initTexture()
{
	if (!this->bgTexture.loadFromFile("Texture/BG/dungeon.jpg"))
		std::cout << "ERROR::BACKGROUND::INITTEXTURE::Could not load texture file." << "\n";
	if (!this->portalTexture.loadFromFile("Texture/BG/Portal.png"))
		std::cout << "ERROR::BACKGROUND::CRYSTAL::INITTEXTURE::Could not load texture file." << "\n";
}

void Background::initVariables()
{
	this->portalTimer.restart();
}

void Background::initBackground()
{
	this->background.setTexture(this->bgTexture);
	this->background.setScale(1.2f, 0.9f);

	this->portal.setTexture(this->portalTexture);
	this->portalFrame = sf::IntRect(0, 0, 50, 200);
	this->portal.setTextureRect(this->portalFrame);
	this->portal.setPosition(925.f, 520.f);
	this->portal.setScale(1.f, .85f);

	//GameOver
	this->bgGameOver.setTexture(this->bgTexture);
	this->bgGameOver.setScale(1.2f, 0.9f);
	this->bgGameOver.setColor(sf::Color(255, 255, 255, 50));
}

//Con/Des
Background::Background()
{
	this->initTexture();
	this->initBackground();
}

Background::~Background()
{
}

const sf::FloatRect Background::getBoundsPortal() const
{
	return this->portal.getGlobalBounds();
}

const sf::Sprite Background::getBGGameOver() const
{
	return this->bgGameOver;
}

void Background::animPortal()
{
	if (this->portalTimer.getElapsedTime().asSeconds() >= 0.2)
	{
		this->portalFrame.left += 50.f;
		if (this->portalFrame.left >= 150.f)
		{
			this->portalFrame.left = 0;
		}

		this->portalTimer.restart();
		this->portal.setTextureRect(this->portalFrame);
	}
}

//functions
void Background::updates()
{
	this->animPortal();
}

void Background::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->portal);
}