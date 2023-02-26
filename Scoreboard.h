#pragma once

#include <stdio.h>
#include "iostream"
#include "vector"
#include "sstream"
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

class Scoreboard
{
private:
	sf::Text text;
	sf::Texture backgroundTex;
	sf::Sprite background;

	void initBackground();
public:
	Scoreboard(int x, int y, std::string word, sf::Font* font);
	virtual ~Scoreboard();

	//Functinos
	void getSize();
	void setFontColor(sf::Color color);
	void setFontSize(int size);

	//Render
	void renderBackground(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};