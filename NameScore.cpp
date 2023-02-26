#include "NameScore.h"

void NameScore::initVariables()
{
	this->isSelected = false;
	this->hasLimit = false;
	this->textbox.setCharacterSize(100);
	this->textbox.setFillColor(sf::Color(255, 215, 0));
}

NameScore::NameScore(bool sel)
{
	this->initVariables();
	this->initBackground();
	this->initText();
	this->isSelected = sel;
	if (sel)
	{
		this->textbox.setString("");
	}
	else
	{
		this->textbox.setString("");
	}
}

NameScore::~NameScore()
{
}

void NameScore::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
	{
		this->text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY)
	{
		if (this->text.str().length() > 0)
		{
			this->deleteLastChar();
		}
	}
	this->textbox.setString(this->text.str() + "");
}

void NameScore::initBackground()
{
	//Background
	if (!this->backgroundTex.loadFromFile("Texture/BG/Menu/bg.jpg"))
	{
		std::cout << "ERROR::NAMESCORE::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->background.setTexture(this->backgroundTex);

	//Box
	this->rectangleBox.setSize(sf::Vector2f(520.f, 100.f));
	this->rectangleBox.setPosition(sf::Vector2f(710.f, 480.f));
	this->rectangleBox.setFillColor(sf::Color(0, 0, 0, 150));
}

void NameScore::initText()
{
	if (!this->font.loadFromFile("Font/SF.ttf"))
		std::cout << "ERROR::NAMESCORE::Failed to load font" << "\n";
	this->textEnterName.setFont(this->font);
	this->textEnterName.setPosition(375, 25);
	this->textEnterName.setString("Enter  your  name");
	this->textEnterName.setOutlineThickness(10);
	this->textEnterName.setCharacterSize(150);
}

void NameScore::deleteLastChar()
{
	std::string t = this->text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++)
	{
		newT += t[i];
	}
	this->text.str("");
	this->text << newT;
	this->textbox.setString(text.str());
}

void NameScore::setFont(sf::Font& font)
{
	this->textbox.setFont(font);
}

void NameScore::setPosition(sf::Vector2f pos)
{
	this->textbox.setPosition(pos);
}


void NameScore::setColor(sf::Color color)
{
	this->textbox.setFillColor(color);
}


void NameScore::setLimit(bool ToF, int lim)
{
	this->hasLimit = ToF;
	this->limit = lim;
}


void NameScore::setCharSize(int size)
{
	this->textbox.setCharacterSize(size);
}

void NameScore::setOutline(int outlineSize, sf::Color color)
{
	this->textbox.setOutlineColor(color);
	this->textbox.setOutlineThickness(outlineSize);
}

void NameScore::setSelected(bool sel)
{
	this->isSelected = sel;
	if (!sel)
	{
		std::string t = this->text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		this->textbox.setString(newT);
	}
}

void NameScore::typedOn(sf::Event input)
{
	if (this->isSelected)
	{
		int charTyped = input.text.unicode;
		if (charTyped < 128)
		{
			if (this->hasLimit)
			{
				if (this->text.str().length() <= this->limit)
				{
					this->inputLogic(charTyped);
				}
				else if (this->text.str().length() > this->limit && charTyped == DELETE_KEY)
				{
					this->deleteLastChar();
				}
			}
			else
			{
				this->inputLogic(charTyped);
			}
		}
	}
}

std::string NameScore::getText()
{
	return this->text.str();
}

void NameScore::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->rectangleBox);
	target.draw(this->textbox);
	target.draw(this->textEnterName);
}
