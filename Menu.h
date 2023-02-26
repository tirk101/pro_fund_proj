#pragma once
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

class Menu
{
private:
	//BG
	sf::Texture textureMenuBG;
	sf::Sprite spriteMenuBG;

	//LOGO
	sf::Texture textureMenuLOGO;
	sf::Sprite spriteMenuLOGO;
	
	//START
	sf::Texture textureMenuStart;
	sf::Sprite spriteMenuStart;
	
	//Score
	sf::Texture textureMenuScore;
	sf::Sprite spriteMenuScore;

	//Text
	sf::Text ExitText;

	//NAME
	sf::Font font;
	sf::Text name;
	sf::Text number;

	int delaySel;

	//Private Function
	void initVariables();
	void initTexture();
	void initSprite();
	void initNameKMITL();
	void initText();

	//Variables
	int selectedMenu;
	int fontSize;
	int fontThickness;
	int selectedDelay;
	int selectedDelayMax;
	int GameState;

public:
	Menu();
	virtual ~Menu();

	//Assescor
	const int& getGameState() const;

	//Update
	void updateInput();
	void setToMenu();

	//render
	void render(sf::RenderTarget& target);
};
