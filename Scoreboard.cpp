#include "Scoreboard.h"

void Scoreboard::initBackground()
{
	if (!this->backgroundTex.loadFromFile("Texture/BG/Menu/bg.jpg"))
	{
		std::cout << "ERROR::SCOREBOARD::INITTEXTURE::Could not load textures file." << "\n";
	}
	
	this->background.setTexture(this->backgroundTex);
}

Scoreboard::Scoreboard(int x, int y, std::string word, sf::Font* font)
{
	this->initBackground();

	this->text.setFont(*font);
	this->text.setPosition(x, y);
	this->text.setString(word);
	this->text.setOutlineThickness(10);
	this->text.setCharacterSize(100);
}

Scoreboard::~Scoreboard()
{
}

void Scoreboard::getSize()
{
	this->text.getGlobalBounds().width;
}

void Scoreboard::setFontColor(sf::Color color)
{
	this->text.setFillColor(color);
}

void Scoreboard::setFontSize(int size)
{
	this->text.setCharacterSize(size);
}

void Scoreboard::renderBackground(sf::RenderTarget& target)
{
	target.draw(this->background);
}

void Scoreboard::render(sf::RenderTarget& target)
{
	target.draw(this->text);
}
