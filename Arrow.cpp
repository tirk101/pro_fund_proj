#include "Arrow.h"

void Arrow::initTexture()
{
	if (!this->arrowTex.loadFromFile("Texture/Bullet/Arrow.png"))
	{
		std::cout << "ERROR::ARROW::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Arrow::initArrow()
{
	this->arrow.setTexture(this->arrowTex);
	this->arrow.setScale(0.04f, 0.07f);
	
}

Arrow::Arrow(float dirPlayer, float posX, float posY, float dirX, float dirY, float movementspeed)
{
	if (dirPlayer == 0) this->arrow.setRotation(-90.f);	//Top
	else if (dirPlayer == 1) this->arrow.setRotation(180.f); //Left
	else if (dirPlayer == 2) this->arrow.setRotation(90.f); //Under
	else if (dirPlayer == 3) this->arrow.setRotation(0.f); //Right
	
	this->arrow.setPosition(posX, posY);
	this->dirArrow.x = dirX;
	this->dirArrow.y = dirY;
	this->movementSpeed = movementspeed;
	
	//Initialize
	this->initTexture();
	this->initArrow();
}

Arrow::~Arrow()
{
}

const sf::FloatRect Arrow::getBounds() const
{
	return this->arrow.getGlobalBounds();
}

void Arrow::updates()
{
	//Movement
	this->arrow.move(this->movementSpeed * this->dirArrow);
}

void Arrow::render(sf::RenderTarget& target)
{
	target.draw(this->arrow);
}
