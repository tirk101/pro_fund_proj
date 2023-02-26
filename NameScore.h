#pragma once
#include "iostream"
#include "vector"
#include "sstream"
#include<utility>
#include<algorithm>
#include<string>
#include<vector>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class NameScore
{
private:
	sf::Text textbox;
	sf::Text textEnterName;
	sf::Texture backgroundTex;
	sf::Sprite background;
	sf::Font font;
	std::ostringstream text;
	sf::RectangleShape rectangleBox;
	bool isSelected;
	bool hasLimit;
	int limit;
	//Init
	void initVariables();
	void initBackground();
	void initText();

	//Function
	void inputLogic(int charTyped);
	void deleteLastChar();


public:
	NameScore(bool sel);
	virtual ~NameScore();

	//Functions
	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void setColor(sf::Color color);
	void setCharSize(int size);
	void setLimit(bool ToF, int lim);
	void setOutline(int outlineSize, sf::Color color);
	void setSelected(bool sel);
	void typedOn(sf::Event input);

	//Assescor
	std::string getText();

	//render
	void render(sf::RenderTarget& target);
};

