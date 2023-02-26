#include "Menu.h"

void Menu::initVariables()
{
	this->GameState = 1;
	this->delaySel = 0;
}

void Menu::initTexture()
{
	//Background
	if (!this->textureMenuBG.loadFromFile("Texture/BG/Menu/bg.jpg"))
	{
		std::cout << "ERROR::MENU::BG::INITTEXTURE::Could not load textures file." << "\n";
	}

	//LOGO
	if (!this->textureMenuLOGO.loadFromFile("Texture/BG/Menu/Logo.PNG"))
	{
		std::cout << "ERROR::MENU::BG::INITTEXTURE::Could not load textures file." << "\n";
	}

	//Start
	if (!this->textureMenuStart.loadFromFile("Texture/BG/Menu/START.png"))
	{
		std::cout << "ERROR::MENU::START::INITTEXTURE::Could not load textures file." << "\n";
	}

	//Score
	if (!this->textureMenuScore.loadFromFile("Texture/BG/Menu/SCORE.png"))
	{
		std::cout << "ERROR::MENU::SCORE::INITTEXTURE::Could not load textures file." << "\n";
	}
}

void Menu::initSprite()
{
	//Background
	this->spriteMenuBG.setTexture(this->textureMenuBG);

	//LOGO
	this->spriteMenuLOGO.setTexture(this->textureMenuLOGO);
	this->spriteMenuLOGO.setScale(0.4f, 0.4f);
	this->spriteMenuLOGO.setPosition(150.f, 70.f);

	//Start
	this->spriteMenuStart.setTexture(this->textureMenuStart);
	this->spriteMenuStart.scale(1.f, 1.f);
	this->spriteMenuStart.setOrigin(sf::Vector2f(this->textureMenuStart.getSize().x / 2, this->textureMenuStart.getSize().y / 2));
	this->spriteMenuStart.setPosition(950.f, 580.f);
	
	//Score
	this->spriteMenuScore.setTexture(this->textureMenuScore);
	this->spriteMenuScore.scale(1.f, 1.f);
	this->spriteMenuScore.setOrigin(sf::Vector2f(this->textureMenuScore.getSize().x / 2, this->textureMenuScore.getSize().y / 2));
	this->spriteMenuScore.setPosition(950.f, 800.f);
}

void Menu::initNameKMITL()
{
	if (!this->font.loadFromFile("Font/SF.ttf"))
		std::cout << "ERROR::MENU::Failed to load font" << "\n";

	this->name.setFont(this->font);
	this->name.setPosition({ 0, 1080 / 2 + 400 });
	this->name.setString("KRIT TANGPINYOPUTTIKHUN");
	this->name.setFillColor(sf::Color(252, 183, 138));
	this->name.setOutlineThickness(5);
	this->name.setCharacterSize(50);

	this->number.setFont(this->font);
	this->number.setPosition({ 0, 1080 / 2 + 450 });
	this->number.setString("64010022");
	this->number.setFillColor(sf::Color(252, 183, 138));
	this->number.setOutlineThickness(5);
	this->number.setCharacterSize(50);
}

void Menu::initText()
{
	this->ExitText.setFont(this->font);
	this->ExitText.setPosition( 1920 / 2 + 550, 1080 / 2 + 450 );
	this->ExitText.setString("Press ESC To Exit the Game...");
	this->ExitText.setFillColor(sf::Color::White);
	this->ExitText.setOutlineThickness(5);
	this->ExitText.setCharacterSize(30);
}

Menu::Menu()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initNameKMITL();
	this->initText();
}

Menu::~Menu()
{
}

const int& Menu::getGameState() const
{
	return this->GameState;
}

void Menu::updateInput()
{
	this->delaySel++;

	//Update Input Selected Menu
	if (sf::Mouse::getPosition().x >= 733.f && sf::Mouse::getPosition().y >= 533 && sf::Mouse::getPosition().x <= 1209.f && sf::Mouse::getPosition().y <= 728.f)
	{
		this->spriteMenuStart.setScale(1.1f, 1.1f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Input Name
			this->GameState = 5;
		}
	}
	else if (sf::Mouse::getPosition().x >= 720.f && sf::Mouse::getPosition().y >= 745 && sf::Mouse::getPosition().x <= 1200.f && sf::Mouse::getPosition().y <= 910.f)
	{
		this->spriteMenuScore.setScale(1.1f, 1.1f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//Score Board
			this->GameState = 4;
		}
	}
	else
	{
		this->spriteMenuStart.setScale(1.f, 1.f);
		this->spriteMenuScore.setScale(1.f, 1.f);
	}
	
	//EXIT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && delaySel > 10)
	{
	this->GameState = 0;
	this->delaySel = 0;
	}
}

void Menu::setToMenu()
{
	this->GameState = 1;
	this->delaySel = 0;
}

void Menu::render(sf::RenderTarget& target)
{
	target.draw(this->spriteMenuBG);
	target.draw(this->spriteMenuLOGO);
	target.draw(this->spriteMenuStart);
	target.draw(this->spriteMenuScore);

	target.draw(this->name);
	target.draw(this->number);
	target.draw(this->ExitText);
}